document.getElementById("contact-form").addEventListener("submit", function(event) {
    event.preventDefault();

    // Retrieve form data
    var name = document.getElementById("name").value;
    var email = document.getElementById("email").value;
    var subject = document.getElementById("subject").value;
    var message = document.getElementById("message").value;
    var phone = document.getElementById("phone").value;
    var phoneType = document.getElementById("phone-type").value;

    // Do something with the form data (e.g., send it to a server)
    console.log("Name: " + name);
    console.log("Email: " + email);
    console.log("Subject: " + subject);
    console.log("Message: " + message);
    console.log("Phone: " + phone);
    console.log("Phone Type: " + phoneType);

    // Reset the form
    document.getElementById("contact-form").reset();
  });
