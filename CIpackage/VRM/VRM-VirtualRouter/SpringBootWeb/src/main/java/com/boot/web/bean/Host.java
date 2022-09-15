package com.boot.web.bean;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Host {
    private int hostId;
    private String hostName;
    private String hostAddress;

    public void setHostAddress(String hostAddress) {
        if (hostAddress.split(":").length != 2) {
            System.err.println(hostAddress + " is not a valid url address.");
            System.exit(-102);
        }
        this.hostAddress = hostAddress;
    }
}
