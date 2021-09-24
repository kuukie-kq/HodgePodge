package com.hello.world.controller;

import com.hello.world.service.HomeService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import net.sf.json.JSONArray;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping("/swagger")
@Api(tags = "Demo模块")
public class SwaggerDemoController {
    @Autowired
    private HomeService homeService;

    @RequestMapping(value = "/entrance", method = RequestMethod.POST)
    @ResponseBody
    @ApiOperation(value = "分析页首次访问", notes = "程序初始化数据")
    public String swaggerEntrance() {
        JSONArray jsonArray = JSONArray.fromObject(homeService.getSource());
        return jsonArray.toString();
    }

    @RequestMapping(value = "/demos", method = RequestMethod.POST)
    @ResponseBody
    @ApiOperation(value = "分析页访问", notes = "程序mysql数据")
    public String swaggerDemos() {
        JSONArray jsonArray = JSONArray.fromObject(homeService.getDataFromBase());
        return jsonArray.toString();
    }

    @RequestMapping(value = "/demopage", method = RequestMethod.POST)
    @ResponseBody
    @ApiOperation(value = "分析页访问分页", notes = "分页程序mysql数据")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "page", value = "page", required = true, dataType = "int")
    })
    public String swaggerPageDemos(int page) {
        JSONArray jsonArray = JSONArray.fromObject(homeService.getDataFromBaseByPage(page,5));
        return jsonArray.toString();
    }
}
