package com.boot.web.bean.data;

import com.boot.web.bean.Router;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class RouterMessage {
    private int pageCountNumber;
    private int countPageNumber;
    private int pageNumber;
    private int countNumber;
    private List<Router> routers;
}
