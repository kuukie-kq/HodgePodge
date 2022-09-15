package com.boot.web.dao.impl;

import com.boot.web.bean.Host;
import com.boot.web.bean.HostRelationship;
import com.boot.web.dao.HostRelationshipDao;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

@Repository
public class HostRelationshipDaoImpl implements HostRelationshipDao {
    @Autowired
    JdbcTemplate jdbcTemplate;

    @Override
    public List<HostRelationship> lookupHostShipGetHostShips() {
        List<HostRelationship> relationships = new ArrayList<>();
        String sql = "select * from db_host_relationship";

        List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql);
        for (Map<String,Object> map : maps) {
            HostRelationship relationship = new HostRelationship();
            relationship.setHostShipId(Integer.parseInt(map.get("hostShipId").toString()));
            relationship.setHostId(Integer.parseInt(map.get("hostId").toString()));
            relationship.setRouterId(Integer.parseInt(map.get("routerId").toString()));
            relationships.add(relationship);
        }
        return relationships;
    }

    @Override
    public int lookupHostShipGetHostShipsNumber() {
        String sql = "select count(*) from db_host_relationship";
        return jdbcTemplate.queryForObject(sql,Integer.class);
    }

    @Override
    public List<HostRelationship> lookupHostShipGetHostShipsByLimit(int page) {
        List<HostRelationship> hostRelationships = new ArrayList();
        String sql = "select * from db_host_relationship limit ?,?";
        int start = page * 5;
        int end = (page + 1) * 5;

        List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql,start,end);
        for (Map<String,Object> map : maps) {
            HostRelationship relationship = new HostRelationship();
            relationship.setHostShipId(Integer.parseInt(map.get("hostShipId").toString()));
            relationship.setHostId(Integer.parseInt(map.get("hostId").toString()));
            relationship.setRouterId(Integer.parseInt(map.get("routerId").toString()));
            hostRelationships.add(relationship);
        }
        return hostRelationships;
    }

    @Override
    public HostRelationship lookupHostShipGetHostShipById(int id) {
        HostRelationship relationship = new HostRelationship();
        String sql = "select * from db_host_relationship where hostId=?";

        List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql, id);
        for (Map<String,Object> map : maps) {
            relationship.setHostShipId(Integer.parseInt(map.get("hostShipId").toString()));
            relationship.setHostId(Integer.parseInt(map.get("hostId").toString()));
            relationship.setRouterId(Integer.parseInt(map.get("routerId").toString()));
        }
        return relationship;
    }

    @Override
    public boolean lookHostShipByRouterAndHostId(int hostId, int routerId) {
        String sql = "insert into db_host_relationship values(?,?,?)";
        jdbcTemplate.update(sql,lookupHostShipGetHostShipsNumber()+1,hostId,routerId);
        return true;
    }
}
