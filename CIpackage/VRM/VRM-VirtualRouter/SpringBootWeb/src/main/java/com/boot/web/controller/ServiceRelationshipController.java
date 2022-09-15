package com.boot.web.controller;

import com.boot.web.service.RelationshipService;
import net.sf.json.JSONArray;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping(value = "/service")
public class ServiceRelationshipController {
    @Autowired
    RelationshipService relationshipService;

    @RequestMapping(value = "/routerShip", method = RequestMethod.POST)
    @ResponseBody
    public String relationshipEntrance() {
        JSONArray jsonArray = JSONArray.fromObject(relationshipService.getRouterShip());
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }
}
