jQuery(document).ready(function ($) {

    $(window).scroll(function () {
      if ($(window).scrollTop() > 200) {
          $('nav').addClass('fixed-nav');
      } else {
          $('nav').removeClass('fixed-nav');
      }
  })
  });

  // document.addEventListener('contextmenu', event => event.preventDefault()); --> onemogućavanje desnog klika (stavljeno za probu)

  const navToggle = document.querySelector('.nav-toggle');
  const navLinks = document.querySelector('.links');
  const overlay  = document.querySelector(".overlay")
  const addBtn = document.querySelector(".addBtn");
  
  document.addEventListener("DOMContentLoaded", () => {
    const expandsMore = document.querySelectorAll("[expand-more]")
  
    function expand() {
      const showContent = document.getElementById(this.dataset.target)
      if (showContent.classList.contains('expand-active')) {
        this.innerHTML=this.dataset.showtext
      } else {
        this.innerHTML=this.dataset.hidetext
      }
      showContent.classList.toggle('expand-active')
    }
  
    expandsMore.forEach(expandMore => {
      expandMore.addEventListener("click", expand)
    })
  });
  // Hamburger
  
  navToggle.addEventListener("click", () => {
    document.body.classList.toggle('nav-open');
    
    if (overlay.style.width === "100%") {
      overlay.style.width = "0%";
        
    } else {
        overlay.style.width = "100%";
    }
  });
  
  // AC-PL
  const accordion = document.querySelector('.accordion');
  const items = accordion.querySelectorAll('.accordion__item');
  
  items.forEach((item) => {
    const title = item.querySelector('.accordion__title');
    
    title.addEventListener('click', (e) => {
      const opened_item = accordion.querySelector('.is-open');
      
      toggle_item(item); 
      if (opened_item && opened_item !== item) {
        toggle_item(opened_item);
      }
    });
  });
  
  const toggle_item = (item) => {
    const body = item.querySelector('.accordion__body');
    const content = item.querySelector('.accordion__content');
          
    if (item.classList.contains('is-open')) {
      body.removeAttribute('style');
      item.classList.remove('is-open');
    }
    else {
      body.style.height = body.scrollHeight + 'px';
      item.classList.add('is-open');
    }    
 }