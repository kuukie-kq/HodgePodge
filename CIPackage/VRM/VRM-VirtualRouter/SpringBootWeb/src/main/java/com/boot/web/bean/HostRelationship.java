package com.boot.web.bean;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class HostRelationship {
    private int hostShipId;
    private int hostId;
    private int routerId;
}
