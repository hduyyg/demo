package com.example.demo;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.ApplicationContext;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashMap;
import java.util.Map;

@RestController
@RequestMapping
public class Controller {

    @Autowired
    private ApplicationContext context;

    @GetMapping("/test")
    public Map<String, String> test() {
        Map<String, String> map = new HashMap<>();
        map.put("singleton", context.getBean("singleton").toString());
        map.put("prototype", context.getBean("prototype").toString());
        map.put("session", context.getBean("session").toString());
        map.put("request", context.getBean("request").toString());
        return map;
    }
}
