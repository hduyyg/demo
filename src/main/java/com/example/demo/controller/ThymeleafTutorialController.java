package com.example.demo.controller;

import com.example.demo.dao.UserRepository;
import com.example.demo.dao.model.User;
import com.example.demo.model.BaseResponse;
import com.google.common.collect.Lists;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.io.Serializable;

/**
 * @author yuyan
 */
@Controller
@RequestMapping("/tutorial")
public class ThymeleafTutorialController {

    @Autowired
    private UserRepository userRepository;

    @GetMapping("/demo")
    public String hello(Model model) {
        model.addAttribute("name", "zichuan");

        Info info = new Info();
        info.setName("xxxxx");
        model.addAttribute("info", info);

        model.addAttribute("infos", Lists.newArrayList(info, info, info));

        model.addAttribute("users", userRepository.findAll());

        model.addAttribute("user", new User());

        return "tutorial/demo";
    }

    @ResponseBody
    @GetMapping("/getInfo")
    public BaseResponse getInfos(@RequestParam String name) {
        Info info = new Info();
        info.setName(name);
        return BaseResponse.success(info);
    }

    @Data
    @NoArgsConstructor
    @AllArgsConstructor
    public static class Info implements Serializable {
        private String name;
    }
}