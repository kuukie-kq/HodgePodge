package com.java.main.self;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(value=ElementType.METHOD)//������Ϊ����
@Retention(RetentionPolicy.RUNTIME)//ע����Ϣ����������ʱ
public @interface Mytest {
	
}
