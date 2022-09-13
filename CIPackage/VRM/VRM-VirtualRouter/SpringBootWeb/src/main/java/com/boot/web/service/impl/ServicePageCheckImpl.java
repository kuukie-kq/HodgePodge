package com.boot.web.service.impl;

import com.boot.web.service.ServicePageCheck;
import org.springframework.stereotype.Service;

@Service
public class ServicePageCheckImpl implements ServicePageCheck {
    @Override
    public int pageCheck(int page) {
        if (page > 0) {
            return page-1;
        } else {
            return 0;
        }
    }
}
