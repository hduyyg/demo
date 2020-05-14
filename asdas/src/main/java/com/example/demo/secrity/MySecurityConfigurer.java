package com.example.demo.secrity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.method.configuration.EnableGlobalMethodSecurity;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;

@Configuration
@EnableWebSecurity
@EnableGlobalMethodSecurity(prePostEnabled = true)
public class MySecurityConfigurer extends WebSecurityConfigurerAdapter {

    @Autowired
    MyAuthenticationSuccessHandler myAuthenticationSuccessHandler;

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        System.out.println("MySecurityConfigurer HttpSecurity 调用...");
        http.authorizeRequests()
                .antMatchers("/login").permitAll()
                .antMatchers("/", "/home").hasRole("ROCKET")
                .antMatchers("/admin/**").hasAnyRole("LAKER", "HEAT")
                .anyRequest().authenticated()
                .and()
                .formLogin().loginPage("/login")
                .defaultSuccessUrl("/home").permitAll()
//                .successHandler(new MyAuthenticationSuccessHandler())
                .usernameParameter("username").passwordParameter("password")
                .and()
                .logout().permitAll()
                .and()
                .exceptionHandling().accessDeniedPage("/accessDenied");
        http.csrf().disable();
    }

    @Override
    protected void configure(AuthenticationManagerBuilder auth) throws Exception {
        System.out.println("MySecurityConfigurer AuthenticationManagerBuilder 调用...");
        auth.inMemoryAuthentication().passwordEncoder(new MyPasswordEncoder())
                .withUser("t-mac").password("rocket1").roles("ROCKET");
        auth.inMemoryAuthentication().passwordEncoder(new MyPasswordEncoder())
                .withUser("james").password("laker23").roles("LAKER", "HEAT");
    }
}