import random
from system.service.bottle import static_file, response, Bottle, request
from system.service.proxy_tool import ModelList, ModelTextures, Hitokoto
from system.service.sys_format_tool import op_print as hint


class Server:
    """
    Live2D后端接口部分
    主要是因为由于网络环境的影响，容易出现加载不出来的情况，固将资源本地化
    """

    def __init__(self):
        self._bottle_server = Bottle()

        @self._bottle_server.hook("before_request")
        def validate():
            request_method = request.environ.get('REQUEST_METHOD')

            http_access_control_request_method = request.environ.get('HTTP_ACCESS_CONTROL_REQUEST_METHOD')
            if request_method == 'OPTIONS' and http_access_control_request_method:
                request.environ['REQUEST_METHOD'] = http_access_control_request_method

        @self._bottle_server.hook("after_request")
        def enable():
            response.headers["Access-Control-Allow-Origin"] = "*"
            # response.headers["Access-Control-Allow-Credentials"] = True
            response.headers["Access-Control-Allow-Headers"] = "*"

        @self._bottle_server.route("/get/")
        def get():
            if request.query.id is None:
                return
            get_id = request.query.id or "1-23"
            modelList = ModelList("./static/live2d/model_list.json")
            modelTextures = ModelTextures()
            if get_id.split("-").__len__() != 2:
                return
            modelId = int(get_id.split("-")[0])
            modelTexturesId = int(get_id.split("-")[1])
            # 资源最外层获取基础路径
            modelName = modelList.id_to_name(modelId)
            if type(modelName) == list:
                # 简单处理既直接默认，未做复杂逻辑处理
                modelName = modelName[0]
            # 资源信息及修改处理
            modelJson = ModelList("./static/live2d/model/%s/index.json" % modelName).get_list()
            if modelTexturesId > 0:
                modelTexturesName = modelTextures.get_name(modelName, modelTexturesId)
                modelJson["textures"] = modelTexturesName
            for i in range(0, modelJson["textures"].__len__()):
                modelJson["textures"][i] = "../model/%s/%s" % (modelName, modelJson["textures"][i])
            modelJson["model"] = "../model/%s/%s" % (modelName, modelJson["model"])
            if "pose" in modelJson:
                modelJson["pose"] = "../model/%s/%s" % (modelName, modelJson["pose"])
            if "physics" in modelJson:
                modelJson["physics"] = "../model/%s/%s" % (modelName, modelJson["physics"])
            if "motions" in modelJson:
                for key_i, i in modelJson["motions"].items():
                    for j in range(0, i.__len__()):
                        for key_k, k in i[j].items():
                            if "file" == key_k:
                                modelJson["motions"][key_i][j][key_k] = "../model/%s/%s" % (modelName, k)
                # 目的 把含有的路径加上前缀
                pass
            if "expressions" in modelJson:
                for i in range(0, modelJson["expressions"].__len__()):
                    for key_j, j in modelJson["expressions"][i].items():
                        if "file" == key_j:
                            modelJson["expressions"][i][key_j] = "../model/%s/%s" % (modelName, j)
                # 目的 把含有的路径加上前缀
                pass
            response.headers.append("Content-type", "application/json")
            return modelJson

        @self._bottle_server.route("/model/<path:path>")
        def resource(path):
            return static_file(path, root="./static/live2d/model/")

        @self._bottle_server.route("/rand_textures/")
        def clothing():
            if request.query.id is None:
                return
            get_id = request.query.id or "1-23"
            modelList = ModelList("./static/live2d/model_list.json")
            modelTextures = ModelTextures()
            if get_id.split("-").__len__() != 2:
                return
            modelId = int(get_id.split("-")[0])
            modelTexturesId = int(get_id.split("-")[1])
            modelName = modelList.id_to_name(modelId)
            # 随机查找同模型下的不同资源
            if type(modelName) == list:
                # 简单处理既直接默认，未做复杂逻辑处理
                modelName = modelName[0]
            modelTexturesList = modelTextures.get_list(modelName)
            modelTexturesIndex = 0
            if modelTexturesList is not None and modelTexturesList.__len__() > 1:
                for i in iter(int, 1):
                    i.__sizeof__()
                    modelTexturesIndex = random.choice(range(modelTexturesList.__len__())) + 1
                    if modelTexturesId != modelTexturesIndex:
                        break
            else:
                modelTexturesIndex = 1
            response.headers.append("Content-type", "application/json")
            return modelList.rand_textures_json(modelTexturesIndex, modelTexturesList[modelTexturesIndex-1], modelName)

        @self._bottle_server.route("/rand/")
        def change():
            if request.query.id is None:
                return
            modelId = int(request.query.id or "1")
            modelList = ModelList("./static/live2d/model_list.json")
            modelListJson = modelList.get_list()
            modelRandId = 0
            for i in iter(int, 1):
                i.__sizeof__()
                modelRandId = random.choice(range(modelListJson["models"].__len__())) + 1
                if modelRandId != modelId and (modelRandId == 1 or modelRandId == 3 or modelRandId == 4):
                    # TODO change&delete
                    # 由于删除了一些资源而未修改model_list文件
                    break
            response.headers.append("Content-type", "application/json")
            return modelList.rand_model_json(modelRandId, modelListJson["models"][modelRandId-1], modelListJson["messages"][modelRandId-1])

        @self._bottle_server.route("/hitokoto/rand", method="POST")
        def rand_json():
            # request.method
            rand_one = random.randint(0, 999)
            rand_two = random.randint(0, 999)
            rand_three = random.randint(0, 999)
            json = Hitokoto().get(rand_one, rand_two, rand_three)
            # response.content_type = "application/json" 前端不JSON.parse的情况
            return json

    def run(self):
        from system.argument.situation import Args
        if Args.get_after_api_host() == "127.0.0.1":
            self._bottle_server.run(host=Args.get_after_api_host(), port=Args.get_after_api_port(), debug=True)
        else:
            hint("err", "The address is not local address and do not listen to %s:%d" % (Args.get_after_api_host(), Args.get_after_api_port()))

    pass


def interface_run():
    resource_server = Server()
    resource_server.run()

