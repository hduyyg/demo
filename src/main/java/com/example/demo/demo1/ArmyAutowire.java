package com.example.demo.demo1;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ArmyAutowire {

    @Sword
    @Gun
    @Autowired
    private Knight knight;

    public void fight() {
        knight.fight();
    }
}
