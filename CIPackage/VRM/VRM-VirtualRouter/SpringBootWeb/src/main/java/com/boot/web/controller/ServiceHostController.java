package com.boot.web.controller;

import com.boot.web.service.HostService;
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
public class ServiceHostController {
    @Autowired
    HostService hostService;
    @Autowired
    ServicePageCheck servicePageCheck;

    @RequestMapping(value = "/hostMessage", method = RequestMethod.POST)
    @ResponseBody
    public String hostEntrance() {
        JSONArray jsonArray = JSONArray.fromObject(hostService.getMessage());
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }

    @RequestMapping(value = "/hostPage", method = RequestMethod.POST)
    @ResponseBody
    public String hostPageEvent(@RequestParam int page) {
        JSONArray jsonArray = JSONArray.fromObject(hostService.getMessageByLimit(servicePageCheck.pageCheck(page)));
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }

    @RequestMapping(value = "/addHost", method = RequestMethod.POST)
    @ResponseBody
    public String hostAddEvent(@RequestParam int hostId,@RequestParam String hostName,@RequestParam String hostAddress,@RequestParam String hostShip) {
        JSONArray jsonArray = JSONArray.fromObject(hostService.setNewHostAndShip(hostId,hostName,hostAddress,Integer.parseInt(hostShip)));
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }
}
