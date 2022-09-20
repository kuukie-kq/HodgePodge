package com.boot.web.bean.data;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Relationship {
    private String fromNode;
    private String toNode;
}
