from system.service.bottle import static_file, response, Bottle, request


class Server:
    """
    Web服务部分
    理论充当了一个nginx代理服务器，代理静态资源（既将file://转换成http://）这样就可以解决部分跨域问题
    实现方式采用了bottle框架，提到网站系统，第一个想到的框架是Django，但是由于Django模块化很细（文件等很多）且需求很简单只需要代理静态资源
    通过查阅资料发现有两款更加轻量便捷的框架flask与bottle，对比了解到bottle为单文件，且不依赖任何第三方库，基于系统库封装的（虽然额外一些功能需要使用第三方库内容）正好符合我的预期

    简单的测试发现，同样还是存在跨域问题，且调试过程中由于浏览器的缓存干扰，无法实时判断修改是否解决了跨域问题，暂且搁置
    该服务器作为窗体中的一个守护线程（因为关闭的时候不需要等该线程结束，也结束不了）的形式存在，这会不会有点小题大做考虑换成协程方式运行
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

        @self._bottle_server.route("/html/<path:path>")
        def server_static(path):
            return static_file(path, root="./static/live/")

        @self._bottle_server.route("/welcome/<path:path>")
        def server_web(path):
            return static_file(path, root="./static/local/")

    def run(self):
        from system.argument.situation import Args
        self._bottle_server.run(host=Args.get_front_html_host(), port=Args.get_front_html_port(), debug=True)

    pass


def server_url(html_file):
    from system.argument.situation import front_html_address
    return "{address}/html/{html}".format(address="http://" + front_html_address(), html=html_file)


def render_run():
    bottle_server = Server()
    bottle_server.run()
