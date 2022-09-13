package com.boot.web.service;

import com.boot.web.bean.data.RouterMessage;

public interface RouterService {
    RouterMessage getMessage();
    RouterMessage getMessageByLimit(int page);
    boolean setNewRouter(int routerId,String routerName,String routerAddress);
}
