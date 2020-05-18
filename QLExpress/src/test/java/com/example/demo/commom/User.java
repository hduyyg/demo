package com.example.demo.commom;

import org.apache.commons.lang.StringUtils;

public class User {
    private String name;

    public User() {
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    public static String firstToUpper(String value) {
        if(StringUtils.isBlank(value))
            return "";
        value = StringUtils.trim(value);
        String f = StringUtils.substring(value,0,1);
        String s = "";
        if(value.length() > 1){
            s = StringUtils.substring(value,1);
        }
        return f.toUpperCase() + s;
    }
}