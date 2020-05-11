package com.example.demo.demo6;

import org.springframework.boot.autoconfigure.condition.ConditionalOnBean;
import org.springframework.context.annotation.Conditional;
import org.springframework.stereotype.Component;

@Component
//@Conditional(YahoCondition.class)
@ConditionalOnBean(Yaho.class)
public class God {
}
