package com.boot.web.bean;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Router {
    private int routerId;
    private String routerName;
    private String routerAddress;

    public void setRouterAddress(String routerAddress) {
        if (routerAddress.split(":").length != 2) {
            System.err.println(routerAddress + " is not a valid url address.");
            System.exit(-101);
        }
        this.routerAddress = routerAddress;
    }
}
