package com.boot.web.bean.data;

import com.boot.web.bean.Router;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class RouterShip {
    private List<Router> routers;
    private List<Relationship> ships;
}
