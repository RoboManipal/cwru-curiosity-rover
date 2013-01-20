<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  
  
  <link rel="stylesheet" href="css/global.css">
  
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.5.1/jquery.min.js"></script>
  <script src="js/slides.min.jquery.js"></script>
  <script>
    $(function(){
    // Set starting slide to 1
    var startSlide = 1;
    // Get slide number if it exists
    if (window.location.hash) {
    startSlide = window.location.hash.replace('#','');
    }
    // Initialize Slides
    $('#slides').slides({
    preload: true,
    preloadImage: 'img/loading.gif',
    generatePagination: true,
    play: 5000,
    pause: 2500,
    hoverPause: true,
    // Get the starting slide
    start: startSlide,
    animationComplete: function(current){
    // Set the slide number as a hash
    window.location.hash = '#' + current;
    }
    });
    });
    </script>
</head>
<body>

<div id="header">
        <div class="center">
<!--    <div id="logo"><a href="#">Triumphant Temple of Hope</a></div>-->
                <!--Menu Begin-->
                <div id="menu">
                <ul>
                <li><a class="active" href="index.shtml"><span>Home</span></a></li>
                <li><a href="project.shtml"><span>The Project</span></a></li>
                <li><a href="team.shtml"><span>The Team</span></a></li>
                <li><a href="sponsors.shtml"><span>The Sponsors</span></a></li>
                <li><a href="contact.shtml"><span>Contact Us</span></a></li>
                </ul>
                </div>
                <!--Menu END-->
        </div>
</div>
