package com.example.demo.controller;

import org.springframework.security.core.Authentication;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.context.SecurityContextHolder;

import java.util.ArrayList;
import java.util.List;

public class BaseController {

    protected String getUsername() {
        String name = SecurityContextHolder.getContext().getAuthentication().getName();
        return name;
    }

    protected String getAuthority() {
        Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
        List<String> roles = new ArrayList<>();
        for (GrantedAuthority a:authentication.getAuthorities()) {
            roles.add(a.getAuthority());
        }
        return roles.toString();
    }
}