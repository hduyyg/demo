package com.example.demo.dao.model;

import lombok.Data;
import org.springframework.data.annotation.CreatedDate;
import org.springframework.data.annotation.LastModifiedDate;
import org.springframework.data.jpa.domain.support.AuditingEntityListener;

import javax.persistence.*;

/**
 * 用户支持记录表
 */
@Entity
@Table(name = "user_support_record")
@Data
@EntityListeners(AuditingEntityListener.class)
public class UserSuportRecord {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    /**
     * 提出问题的反馈人
     */
    private String commiter;

    /**
     * 问题描述
     */
    private String desc;

    /**
     * 问题描述链接
     */
    private String descLink;

    /**
     * 当前问题的状态
     */
    private String status;

    /**
     * 解决方案
     */
    private String solution;

    /**
     * 解决方案链接
     */
    private String solutionLink;

    /**
     * 用户为什么会反馈这个问题
     */
    private String cause;

    /**
     * 用户反馈的原因类型
     */
    private String causeType;

    @CreatedDate
    @Column(updatable = false, nullable = false)
    private Long createTime;

    @LastModifiedDate
    @Column(nullable = false)
    private Long updateTime;
}
