package com.boot.web.service;

import com.boot.web.bean.data.Message;
import com.boot.web.bean.data.RouterShip;

import java.util.List;

public interface RelationshipService {
    RouterShip getRouterShip();
    RouterShip autoFoundRouterShip();
    List<Message> getRouterMessages(String key);
}
