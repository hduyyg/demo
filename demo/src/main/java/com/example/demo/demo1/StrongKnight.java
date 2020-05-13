package com.example.demo.demo1;

import org.springframework.stereotype.Component;

@Sword
@Gun
@Component
public class StrongKnight implements Knight {

    @Override
    public void fight() {
        System.out.println("这里是强壮的骑士，敌人见到我们，必定望风而逃");
    }
}
