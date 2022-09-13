package com.boot.web.bean.data;

import com.boot.web.bean.Host;
import com.boot.web.bean.HostRelationship;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class HostMessage {
    private int pageCountNumber;
    private int countPageNumber;
    private int pageNumber;
    private int countNumber;
    private List<Host> hosts;
    private List<HostRelationship> relationships;
}
