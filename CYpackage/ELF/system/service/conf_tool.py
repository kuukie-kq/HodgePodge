import json
import os
import datetime


class ConfigFile:
    def __init__(self, path):
        with open(path, "r", encoding="utf-8", newline="\n") as file:
            self._json = json.load(file)

    def get_front(self):
        return self._json["html"]

    def get_after(self):
        return self._json["api"]

    pass


class TempLive2d:
    _api_address = "127.0.0.1:50025"

    def construction(self):
        temp_file = "./static/live/trash.html"
        code = """
        <!DOCTYPE html>
        <html>
            <head>
                <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
                <title>Pet Live2D</title>
                <link rel="stylesheet" type="text/css" href="assets/waifu.min.css?v=1.4.2"/>
            </head>
            <body>
                <script src="assets/jquery.min.js?v=3.3.1"></script>
        
                <script src="assets/jquery-ui.min.js?v=1.12.1"></script>
        
                <div id="pl2d" class="waifu">
                    <div class="waifu-tips"></div>
                    <canvas id="live2d" width="280" height="250" class="live2d"></canvas>
                    <div class="waifu-tool">
                        <span class="fui-chat"></span>
                        <span class="fui-eye"></span>
                        <span class="fui-user"></span>
                        <span class="fui-photo"></span>
                        <span class="fui-info-circle"></span>
                    </div>
                </div>
        
                <script src="assets/waifu-tips.min.js?v=1.4.2"></script>
                <script src="assets/live2d.min.js?v=1.0.5"></script>
                <script type="text/javascript">
                    live2d_settings['modelId'] = 1;
                    live2d_settings['modelTexturesId'] = 80;
                    live2d_settings['modelStorage'] = true;
                    live2d_settings['waifuSize'] = '280x250';
                    live2d_settings['waifuTipsSize'] = '180x70';
                    live2d_settings['waifuFontSize'] = '12px';
                    live2d_settings['waifuToolFont'] = '14px';
                    live2d_settings['waifuToolLine'] = '20px';
                    live2d_settings['waifuToolTop'] = '-60px';
                    live2d_settings['waifuDraggable'] = 'unlimited';
                    live2d_settings['waifuMinWidth'] = 'disable';
                    live2d_settings['waifuDraggableRevert'] = false;
                    live2d_settings['waifuEdgeSide'] = 'right:0';
                    live2d_settings['modelAPI'] = 'http://%s/';
                    live2d_settings['modelRandMode'] = 'rand';
                    live2d_settings['modelTexturesRandMode'] = 'rand';
                    live2d_settings['hitokotoAPI'] = 'http://%s/hitokoto';
                    initModel("assets/waifu-tips.json?v=1.4.2");
                </script>
            </body>
        </html>

        """ % (TempLive2d._api_address, TempLive2d._api_address)

        with open(temp_file, "w", encoding="utf-8", newline="\n") as file:
            file.write(code)

    pass
