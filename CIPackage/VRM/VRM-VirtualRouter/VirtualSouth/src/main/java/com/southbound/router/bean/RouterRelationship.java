package com.southbound.router.bean;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class RouterRelationship {
    private int routerShipId;
    private int routerIdFrom;
    private int routerIdTo;
}
