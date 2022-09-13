package com.boot.web.controller;

import com.boot.web.service.RouterService;
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
public class ServiceRouterController {
    @Autowired
    RouterService routerService;
    @Autowired
    ServicePageCheck servicePageCheck;

    @RequestMapping(value = "/routerMessage", method = RequestMethod.POST)
    @ResponseBody
    public String routerEntrance() {
        JSONArray jsonArray = JSONArray.fromObject(routerService.getMessage());
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }

    @RequestMapping(value = "/routerPage", method = RequestMethod.POST)
    @ResponseBody
    public String routerPageEvent(@RequestParam int page) {
        JSONArray jsonArray = JSONArray.fromObject(routerService.getMessageByLimit(servicePageCheck.pageCheck(page)));
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }

    @RequestMapping(value = "/addRouter", method = RequestMethod.POST)
    @ResponseBody
    public String routerAddEvent(@RequestParam int routerId, @RequestParam String routerName, @RequestParam String routerAddress) {
        JSONArray jsonArray = JSONArray.fromObject(routerService.setNewRouter(routerId,routerName,routerAddress));
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }
}
