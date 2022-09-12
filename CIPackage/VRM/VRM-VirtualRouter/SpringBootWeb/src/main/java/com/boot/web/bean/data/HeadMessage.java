package com.boot.web.bean.data;

import com.boot.web.bean.HostRelationship;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class HeadMessage {
    private int hostNumber;
    private int routerNumber;
    private int pageCountNumber;
    private int countPageNumber;
    private int pageNumber;
    private int countNumber;
    private List<HostRelationship> hostRelationshipList;
}
