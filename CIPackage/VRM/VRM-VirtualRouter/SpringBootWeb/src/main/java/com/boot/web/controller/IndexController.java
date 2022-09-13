package com.boot.web.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class IndexController {
    @RequestMapping(value = "/board.html")
    public String board() {
        return "board";
    }
    @RequestMapping(value = "/home.html")
    public String home() {
        return "home";
    }
    @RequestMapping(value = "/host.html")
    public String host() {
        return "host";
    }
    @RequestMapping(value = "/index.html")
    public String index() {
        return "index";
    }
    @RequestMapping(value = "/router.html")
    public String router() {
        return "router";
    }
    @RequestMapping(value = "/relationship.html")
    public String routerRelationship() {
        return "relationship";
    }
    @RequestMapping(value = "/timetable.html")
    public String timetable() {
        return "timetable";
    }
}
