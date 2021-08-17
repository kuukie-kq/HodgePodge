package com.java.main.proxy;

import java.io.File;
import java.io.FileWriter;
import java.lang.reflect.Constructor;
import java.net.URL;
import java.net.URLClassLoader;

import javax.tools.JavaCompiler;
import javax.tools.StandardJavaFileManager;
import javax.tools.ToolProvider;
import javax.tools.JavaCompiler.CompilationTask;

//IOC，AOP
public class Proxy {
	public static Object newProxyInstance(String str) throws Exception {
        //生成Java源文件  
        String srcCode = "package com.java.main.proxy;\n\n"
            + "public class $ProxyTest implements ProxyInter {\n"
            + "\tpublic void run() {\n\t\t"
            + str
            + "\n\t}\n"
            + "}\n";
        String fileName = "d:/MyProgram/workspace/KuukieNOWorld/src/com/java/main/proxy/$ProxyTest.java";  
        File f = new File(fileName);
        FileWriter fw = new FileWriter(f);
        fw.write(srcCode);
        fw.flush();
        fw.close();
        
        //将Java文件编译成class文件
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        StandardJavaFileManager fileMgr = compiler.getStandardFileManager(null, null, null);
        Iterable units = fileMgr.getJavaFileObjects(fileName);
        CompilationTask t = compiler.getTask(null, fileMgr, null, null, null, units);
        t.call();
        fileMgr.close();
        
        //加载到内存，并实例化
        URL[] urls = new URL[] {new URL("file:/" + "D:/MyProgram/workspace/KuukieNOWorld/src/")};
        URLClassLoader ul = new URLClassLoader(urls);
        Class c = ul.loadClass("com.java.main.proxy.$ProxyTest");
        
        Constructor ctr = c.getConstructor();
        Object m = ctr.newInstance();
        
        return m;
	}
}
