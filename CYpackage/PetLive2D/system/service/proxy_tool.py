import json
import os


class ModelList:
    def __init__(self, path):
        with open(path, "r", encoding="utf-8") as file:
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
            with open(filepath, "r", encoding="utf-8") as file:
                textures = json.load(file)
        else:
            textures = self.get_textures(name)
            if textures is not None:
                with open(filepath, "w", encoding="utf-8") as file:
                    json.dump(textures, file, indent=4, ensure_ascii=False)
        return textures

    def get_textures(self, name):
        self.__sizeof__()
        textures = []
        for i in os.listdir("./static/live2d/model/%s/textures/" % name):
            textures.append("textures/%s" % i)
        if textures.__len__() == 0:
            return None
        return textures

    pass
