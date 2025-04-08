document.addEventListener("DOMContentLoaded", () => {
    const thumbnails = document.querySelectorAll(".thumbnail");
    const lightbox = document.querySelector(".lightbox");
    const lightboxImage = document.getElementById("lightbox-image");
  
    thumbnails.forEach((thumbnail) => {
      thumbnail.addEventListener("click", () => {
        const imageSrc = thumbnail.getAttribute("data-image");
        lightboxImage.src = imageSrc;
        lightbox.classList.add("active");
  
        if (["img/img1.jpg", "img/img2.jpg"].includes(imageSrc)) {
          lightboxImage.classList.add("rotate");
        } else {
          lightboxImage.classList.remove("rotate");
        }
  
        if (imageSrc === "img/img3.jpg") {
          lightboxImage.classList.add("bounce");
        } else {
          lightboxImage.classList.remove("bounce");
        }

        if (["img/img4.jpg", "img/img5.jpg", "img/img6.jpg" , "img/img7.jpg"].includes(imageSrc)) {
            lightboxImage.classList.add("slide-in-elliptic-bottom-fwd");
          } else {
            lightboxImage.classList.remove("slide-in-elliptic-bottom-fwd");
          }

          if (["img/img8.jpg", "img/img9.jpg", "img/img10.jpg"].includes(imageSrc)) {
            lightboxImage.classList.add("roll-in-blurred-left");
          } else {
            lightboxImage.classList.remove("roll-in-blurred-left");
          }
  
        setTimeout(() => {
          lightboxImage.style.transform = "scale(1) translateY(0)";
          lightboxImage.style.opacity = "1";
        }, 50);
      });
    });
  
    lightbox.addEventListener("click", () => {
      lightboxImage.classList.remove("rotate");
      lightboxImage.classList.remove("bounce");
      lightboxImage.classList.remove("slide-in-elliptic-bottom-fwd");
      lightboxImage.classList.remove("roll-in-blurred-left");

      lightboxImage.classList.add("slide-out-elliptic-top-bck");

      lightboxImage.style.opacity = "0";
      setTimeout(() => {
        lightbox.classList.remove("active");
        lightboxImage.src = "";
      }, 1100);
    });
  });