package com.example.demo.demo1;

import org.springframework.context.annotation.Primary;
import org.springframework.stereotype.Component;

@Primary
@Component
public class WeakKnight implements Knight {

    @Override
    public void fight() {
        System.out.println("这里是菜鸡骑士，我们见到敌人，必定望风而逃");
    }
}
