package com.example.demo.controller;

import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.web.authentication.logout.SecurityContextLogoutHandler;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@Controller
public class MySecurityController extends BaseController{

    @RequestMapping("/")
    @ResponseBody
    public String index() {
        return "首页";
    }

    @RequestMapping("/home")
    @ResponseBody
    public String home() {
        String username = getUsername();
        System.out.println("username = " + username);
        return "主页 - 用户名：" + username;
    }

    @RequestMapping("/login")
    public String login() {
        return "login.html";
    }

    @RequestMapping("/admin")
    @ResponseBody
    public String admin() {
        String username = getUsername();
        String role = getAuthority();
        return "管理页 - 用户名：" + username + " - 角色：" + role;
    }

    @RequestMapping("/nba")
    @ResponseBody
    public String nba() {
        String username = getUsername();
        String role = getAuthority();
        return "NBA - 用户名：" + username + " - 角色：" + role;
    }

    @RequestMapping("/accessDenied")
    @ResponseBody
    public String accessDenied() {
        return "无权限";
    }

    @RequestMapping("/logout")
    @ResponseBody
    public String logout(HttpServletRequest request, HttpServletResponse response) {
        Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
        if (authentication != null) {
            new SecurityContextLogoutHandler().logout(request, response, authentication);
        }
        return "用户登出";
    }
}