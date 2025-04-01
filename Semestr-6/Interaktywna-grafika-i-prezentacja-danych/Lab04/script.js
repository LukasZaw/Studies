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

      setTimeout(() => {
        lightboxImage.style.transform = "scale(1) translateY(0)";
        lightboxImage.style.opacity = "1";
      }, 50);
    });
  });

  lightbox.addEventListener("click", () => {
    lightboxImage.classList.remove("rotate");
    lightboxImage.classList.remove("bounce");
    lightboxImage.style.transform = "scale(0.5) translateY(-50px)";
    lightboxImage.style.opacity = "0";
    setTimeout(() => {
      lightbox.classList.remove("active");
      lightboxImage.src = "";
    }, 500);
  });
});
