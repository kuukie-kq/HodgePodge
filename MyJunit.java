package com.java.main.self;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

public class MyJunit {
	//传入一个对象实例 demo
    public static void run(Class c) throws InstantiationException,IllegalAccessException, IllegalArgumentException,InvocationTargetException {
        Method[] methods = c.getDeclaredMethods();//获取对象声明的方法集合
        List<Method> testList = new ArrayList<Method>();//@Mytest注解的方法集合
        Method afterMethod = null;//@Myafter注解方法
        Method beforeMethod = null;//@Mybefore的注解方法
        for (Method method : methods) {//循环对象声明的所有方法
        //如果有@Mytest注解，则将该方法加入到Mytest注解的方法集合
            if (method.isAnnotationPresent(Mytest.class)) {
                testList.add(method);
            }
            //如果有@Before注解，则引用该方法
            if (method.isAnnotationPresent(Mybefore.class)) {
                beforeMethod = method;
            }
            //如果有@After注解，则引用该方法
            if (method.isAnnotationPresent(Myafter.class)) {
                afterMethod = method;

            }

        }
        //new一个对象实例
        Object obj = c.newInstance();
        //反射激活方法
        for (Method m : testList) {
            if (beforeMethod != null) {
                beforeMethod.invoke(obj, null);
            }

            m.invoke(obj, null);
            if (afterMethod != null) {
                afterMethod.invoke(obj, null);
            }

        }
    }
}
