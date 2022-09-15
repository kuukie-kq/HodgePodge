package com.boot.web.service;

import com.boot.web.bean.data.HeadMessage;

public interface HomeService {
    HeadMessage getMessage();
    HeadMessage getMessageByLimit(int page);
}
