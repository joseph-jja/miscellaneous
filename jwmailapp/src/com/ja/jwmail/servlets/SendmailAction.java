package com.ja.jwmail.servlets;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionErrors;

import com.ja.jwmail.common.SMTPMailMessage;
import com.ja.jwmail.formbeans.AuthenticationRecord;
import com.ja.jwmail.formbeans.BaseFormBean;
import com.ja.jwmail.formbeans.SMTPRecord;
import com.ja.jwmail.services.SMTPService;

public class SendmailAction extends BaseAction {

	@Override
	@SuppressWarnings("unchecked")
	public String processRequest(BaseFormBean form, HttpServletRequest request,
			HttpServletResponse response, HttpSession session) throws Exception {
		
		ActionErrors errors = new ActionErrors(); 
		
		// get the data from the form
		SMTPRecord mail = (SMTPRecord)form;
		
		// get the data from the session authentication record
		AuthenticationRecord authRecord = (AuthenticationRecord)session.getAttribute(BaseAction.AUTH_RECORD);
		if ( authRecord == null ) {
			
			return BaseAction.FAILED;
		}
		
		// get the auth user name
		String smtpAuthUser = authRecord.getUsername() + "@" + authRecord.getMaildomainname();
		
		// create a new mail message
		SMTPMailMessage message = new SMTPMailMessage();
		
		// set details that were not in post
		message.setUsername(smtpAuthUser);
		message.setPassword(authRecord.getPassword());
		
		message.setSmtpAuth(authRecord.isSmtpauth());
		message.setUsessl(authRecord.isSsl());
		message.setUsetls(authRecord.isTls());
		
		// now set the data from the post
		message.setSubject(mail.getSubject());
		message.setMessage(mail.getMessage());
		
		// to, cc and bcc
		String[] toUsers = mail.getToUsers().split(",");
		List<String> mailTo = new ArrayList<String>(toUsers.length);
		for ( int i = 0; i < toUsers.length; i+= 1 ) { 
			mailTo.add(toUsers[i]);
		}
		message.setToUsers(mailTo);
		       
		if ( mail.getCcUsers() != null && mail.getCcUsers().length() > 0 ) { 
			String[] ccUsers = mail.getCcUsers().split(",");
			List<String> mailCC = new ArrayList<String>(ccUsers.length);
			for ( int i = 0; i < ccUsers.length; i+= 1 ) { 
				mailCC.add(ccUsers[i]);
			}
			message.setCcUser(mailCC);
		}
		
		if ( mail.getBccUsers() != null && mail.getBccUsers().length() > 0 ) { 
			String[] bccUsers = mail.getBccUsers().split(",");
			List<String> mailBCC = new ArrayList<String>(bccUsers.length);
			for ( int i = 0; i < bccUsers.length; i+= 1 ) { 
				mailBCC.add(bccUsers[i]);
			}
			message.setBccUser(mailBCC);
		}
		
		message.setFromUser(smtpAuthUser);
		
		// bajamo! send the mail message and hope that it does not blow up
		SMTPService sendmail = new SMTPService(authRecord.getSmtpMailServer(), authRecord.getSmtpPort());
		sendmail.sendMail(message);
		
		return BaseAction.SUCCESS;
	}

}
