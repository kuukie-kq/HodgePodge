package com.boot.web.controller;

import com.boot.web.service.HomeService;
import com.boot.web.service.ServicePageCheck;
import net.sf.json.JSONArray;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping(value = "/service")
public class ServiceHomeController {
    @Autowired
    HomeService homeService;
    @Autowired
    ServicePageCheck servicePageCheck;

    @RequestMapping(value = "/headMessage", method = RequestMethod.POST)
    @ResponseBody
    public String homeEntrance() {
        JSONArray jsonArray = JSONArray.fromObject(homeService.getMessage());
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }

    @RequestMapping(value = "/headPage", method = RequestMethod.POST)
    @ResponseBody
    public String homePageEvent(@RequestParam int page) {
        JSONArray jsonArray = JSONArray.fromObject(homeService.getMessageByLimit(servicePageCheck.pageCheck(page)));
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }
}
