package com.boot.web.service;

import com.boot.web.bean.data.HostMessage;

public interface HostService {
    HostMessage getMessage();
    HostMessage getMessageByLimit(int page);
    boolean setNewHostAndShip(int hostId,String hostName,String hostAddress,int routerId);
}
