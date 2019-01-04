package com.ja.jwmail.tests;

import com.ja.jwmail.services.SMTPService;

import junit.framework.*;
import junit.extensions.*;

import java.util.List;
import java.util.ArrayList;

import com.ja.jwmail.common.SMTPMailMessage;

public class TestSMTPService extends TestCase {

	private String smtpusername;
	private String smtppasswd;
	private String mailfrom;
	private String mailto;
	private String mailhost;
	private int mailport;
	private String mail_subject;
	private String mail_text;
	private boolean smtp_auth;
	private boolean smtp_tls;
	private boolean smtp_ssl;
	
	public TestSMTPService(String name) {
		super(name);

		mailhost = System.getProperty("mailhost");
		mailport = Integer.parseInt(System.getProperty("mailport"));
		
		mailfrom = System.getProperty("mailfrom");
		mailto = System.getProperty("mailto");
		mail_subject = System.getProperty("mail_subject");
		mail_text = System.getProperty("mail_text");
		
		smtpusername = System.getProperty("smtpusername");
		smtppasswd = System.getProperty("smtppasswd");
		smtp_auth = Boolean.parseBoolean(System.getProperty("smtp_auth"));
		smtp_tls = Boolean.parseBoolean(System.getProperty("smtp_tls"));
		smtp_ssl = Boolean.parseBoolean(System.getProperty("smtp_ssl"));
	}
	
	public void testpop3Service() throws Exception {

		SMTPService mailService = new SMTPService(mailhost, mailport);
	
		System.out.println("SMTPService test started!");
		
		SMTPMailMessage msg = new SMTPMailMessage();
		msg.setFromUser(mailfrom);
		
		List<String> to = new ArrayList<String>();
		to.add(mailto);
		msg.setToUsers( to );		
		msg.setSubject(mail_subject);
		msg.setMessage(mail_text);
		
		msg.setSmtpAuth(smtp_auth);
		msg.setUsetls(smtp_tls);
		msg.setUsessl(smtp_ssl);
		msg.setUsername(smtpusername);
		msg.setPassword(smtppasswd);
		
		System.out.println("Message has:");
		System.out.println("\tFrom: " + mailfrom);
		System.out.println("\tTo: " + mailto);
		System.out.println("\tSubject: " + mail_subject);
		System.out.println("\tAuth: " + smtp_auth);
		System.out.println("\tSMTP User: " + smtpusername);
		//System.out.println("\tSMTP Pass: " + smtppasswd);

		mailService.sendMail(msg);
		
		System.out.println("SMTPService test completed!");
	}
}
