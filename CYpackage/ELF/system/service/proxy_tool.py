import os
import json
import datetime


class ModelList:
    def __init__(self, path):
        with open(path, "r", encoding="utf-8", newline="\n") as file:
            self._json = json.load(file)

    def get_list(self):
        return self._json

    def id_to_name(self, index):
        return self._json["models"][index - 1]

    def name_to_id(self, name):
        for i in range(0, self._json["models"].__len__()):
            value = self._json["models"][i]
            if type(value) == list:
                for j in range(0, value.__len__()):
                    if name == value[j]:
                        return i + 1
            else:
                if name == value:
                    return i + 1

    def rand_textures_json(self, index, path, name):
        self.__sizeof__()
        modelRandTextures = {"textures": {"id": index, "name": path, "model": name}}
        return json.dumps(modelRandTextures)

    def rand_model_json(self, index, name, message):
        self.__sizeof__()
        modelRandTextures = {"model": {"id": index, "name": name, "message": message}}
        return json.dumps(modelRandTextures)

    pass


class ModelTextures:
    def __init__(self):
        pass

    def get_name(self, name, index):
        names = self.get_list(name)
        if type(names[index - 1]) == list:
            return names[index - 1]
        return [names[index - 1]]

    def get_list(self, name):
        self.__sizeof__()
        textures = None
        filepath = "./static/live2d/model/%s/textures_cache.json" % name
        if os.path.exists(filepath):
            with open(filepath, "r", encoding="utf-8", newline="\n") as file:
                textures = json.load(file)
        else:
            textures = self._get_textures(name)
            if textures is not None:
                with open(filepath, "w", encoding="utf-8", newline="\n") as file:
                    json.dump(textures, file, indent=4, ensure_ascii=False)
        return textures

    def _get_textures(self, name):
        self.__sizeof__()
        textures = []
        for i in os.listdir("./static/live2d/model/%s/textures/" % name):
            textures.append("textures/%s" % i)
        if textures.__len__() == 0:
            return None
        return textures

    pass


class Hitokoto:
    def __init__(self):
        self._message = ""

    def get(self, x, y, z):
        # 多目录  目录数量出现变动时重新生成dirs_cache.json 1000
        dirpath = "./static/message/dirs_cache.json"
        dirs = None
        if os.path.exists(dirpath):
            with open(dirpath, "r", encoding="utf-8", newline="\n") as file:
                dirs = json.load(file)
        else:
            dirs = self._get_dir()
            if dirs is not None:
                with open(dirpath, "w", encoding="utf-8", newline="\n") as file:
                    json.dump(dirs, file, indent=4, ensure_ascii=False)
        folder = dirs[x % dirs.__len__()]
        # 多文件  文件数量出现变动时重新生成files_cache.json 1000
        cachepath = "./static/message/%s/files_cache.json" % folder
        files = None
        if os.path.exists(cachepath):
            with open(cachepath, "r", encoding="utf-8", newline="\n") as file:
                files = json.load(file)
        else:
            files = self._get_file(folder)
            if files is not None:
                with open(cachepath, "w", encoding="utf-8", newline="\n") as file:
                    json.dump(files, file, indent=4, ensure_ascii=False)
        #
        filepath = "./static/message/%s/%s" % (folder, files[y % files.__len__()])
        messages = None
        if os.path.exists(filepath):
            with open(filepath, "r", encoding="utf-8", newline="\n") as file:
                messages = json.load(file)
        else:
            print(datetime.datetime.now().strftime("[%Y-%m-%d-%H:%M:%S]"), "[-warning-] file", filepath, "is not exists")
            return "{'data': 'ฅ( ̳• ◡ • ̳)ฅ', 'source': 'system-default', 'author': '(⁄ ⁄•⁄ω⁄•⁄ ⁄)'}"
        # bottle返回json非数组直接dictionary即可数组则需要dumps  既内置有json解析
        # return messages[z % messages.__len__()]
        return json.dumps(messages[z % messages.__len__()])

    def _get_dir(self):
        self.__sizeof__()
        textures = []
        for i in os.listdir("./static/message/"):
            textures.append("%s" % i)
        if textures.__len__() == 0:
            return None
        return textures

    def _get_file(self, folder):
        self.__sizeof__()
        textures = []
        for i in os.listdir("./static/message/%s/" % folder):
            textures.append("%s" % i)
        if textures.__len__() == 0:
            return None
        return textures

    pass
