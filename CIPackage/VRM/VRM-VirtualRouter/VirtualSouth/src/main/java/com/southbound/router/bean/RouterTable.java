package com.southbound.router.bean;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class RouterTable {
    private int tableId;
    private String tableName;
    private int routerId;
    private String reachableAddressName;
    private int reachableDistance;
    private String nextAddressName;
}
