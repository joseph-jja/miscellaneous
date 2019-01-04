package com.ja.jwmail.services; 

import java.io.UnsupportedEncodingException;
import java.util.Iterator;
import java.util.List;
import java.util.Properties;
import java.util.Set;

import javax.activation.DataHandler;
import javax.activation.DataSource;
import javax.activation.FileDataSource;
import javax.mail.Authenticator;
import javax.mail.BodyPart;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;

import com.ja.jwmail.common.Pair;
import com.ja.jwmail.common.SMTPMailMessage;
 
public class SMTPService {

    private String mailHost;
    private int mailPort = 25; 
    
    public SMTPService(String mhost) { 
    
        this.mailHost = mhost;        
    
    }

    public SMTPService(String mhost, int port) { 
        
        this.mailHost = mhost;      
        this.mailPort = port;
    
    }

    public void sendMail(SMTPMailMessage mailmessage) 
    	throws UnsupportedEncodingException, MessagingException, Exception 
    { 

    	// Get system properties
	    Properties props = System.getProperties();
    
	    // add mail host to properties
	    props.put("mail.smtp.host", this.mailHost);
	    props.put("mail.smtp.port", this.mailPort );
	    
	    Authenticator auth = null; 
	    
	    // if we are using smtp auth then we do special things
	    if ( mailmessage.isSmtpAuth() ) {
	    	auth = new SMTPAuthenticator(mailmessage.getUsername(), mailmessage.getPassword());

	    	// set properties
	    	props.put("mail.smtp.auth", "true");
	    	props.put("mail.smtp.user", mailmessage.getUsername());

	    	// use tls
	    	if ( mailmessage.isUsetls() ) {
	    		props.put("mail.smtp.starttls.enable","true");
	    	}
	    	
	    	// use ssl
	    	if ( mailmessage.isUsessl() ) {
	    		props.put("mail.smtp.ssl.enable", "true");
	    	}
	    }

	    // get the mail session and pass it the auth which can be null
	    Session session = Session.getInstance(props, auth);
	    //session.setDebug(true);

	    // Define message
	    MimeMessage message = new MimeMessage(session);
	
	    // Set the from address
	    message.setFrom(new InternetAddress(mailmessage.getFromUser()));
	    
	    // to users
	    for ( String toUser : mailmessage.getToUsers() ) {
		    message.addRecipient(Message.RecipientType.TO,new InternetAddress(toUser));
	    }

	    // cc users
	    for ( String ccUser : mailmessage.getCcUser() ) {
		    message.addRecipient(Message.RecipientType.CC,new InternetAddress(ccUser));
	    }

	    // any bcc users
	    for ( String bccUser : mailmessage.getBccUser() ) {
	    	message.addRecipient(Message.RecipientType.BCC,new InternetAddress(bccUser));
	    }
	    
	    // Set the subject
	    message.setSubject(mailmessage.getSubject());
	
	    // get attachments map and manage attachments
	    List<Pair<String, String>> attachments = mailmessage.getAttachments();
	    if ( attachments != null && ! attachments.isEmpty() && attachments.size() > 0 ) { 
	    	// create a new body part, we should call it arms (LOL) and set the message text
		    BodyPart messageBodyPart = new MimeBodyPart();
		    messageBodyPart.setText(mailmessage.getMessage());
		    
		    // create a new multipart mime message in case we have attachments
		    Multipart multipart = new MimeMultipart();
	        multipart.addBodyPart(messageBodyPart);
	        
		    // we have attachments so loop through them
	    	for ( Pair<String, String> fileNames : attachments ) { 
	    		
	    		// the map has the filename of the attachment and the real filename on disk
	    		String attachFilename = fileNames.getKey();
	    		String realfileName = fileNames.getValue();
	    		
	    		// create a new body part for the attachment
	    		BodyPart attachmentBodyPart = new MimeBodyPart();
	    		
	    		// set the datahandler and filename 
	    		DataSource source = new FileDataSource(realfileName);
	    		attachmentBodyPart.setDataHandler(new DataHandler(source));
	    		attachmentBodyPart.setFileName(attachFilename);
	    		
	    		// attach to multipart message
	    		multipart.addBodyPart(attachmentBodyPart);
	    	}	    	
		    message.setContent(multipart);			
	    } else {
	    	// no attachments send simple mail message
	    	message.setText(mailmessage.getMessage());
	    }
	    
	    // Send message
	    // this needs to be done this way so we can support smtp auth
	    if ( mailmessage.isSmtpAuth() ) {
	    	Transport tport = session.getTransport("smtp");
	    	tport.connect(this.mailHost, this.mailPort, mailmessage.getUsername(), mailmessage.getPassword());
	    	tport.sendMessage(message, message.getAllRecipients());
	    	tport.close();
	    } else {
	    	// not auth smtp we do this
	    	Transport.send(message);
	    }
    }
    
  static class SMTPAuthenticator extends Authenticator {
	  
	  private String username;
	  private String password;

	  public SMTPAuthenticator(String username, String passwd) { 
		  super();
		  this.username = username;
		  this.password = passwd;
	  }


	  public PasswordAuthentication getPasswordAuthentication() {
		  return new PasswordAuthentication(this.username, this.password);
	  }
	}
}

