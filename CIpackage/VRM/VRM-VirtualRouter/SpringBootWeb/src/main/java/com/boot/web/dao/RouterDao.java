package com.boot.web.dao;

import com.boot.web.bean.Router;

import java.util.List;

public interface RouterDao {
    List<Router> lookupRouterGetRouters();
    List<Router> lookupRouterGetRoutersByLimit(int page);
    Router lookupRouterById(int id);
    Router lookupRouterByName(String name);
    int lookupRouterGetRoutersNumber();
    boolean lookRouter(Router router);
}
