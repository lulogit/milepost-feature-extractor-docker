alias mp_feat_ex='sudo docker run --mount type=bind,src=$(pwd),dst=/sources -ti lullo/milepost-feature-extractor:slim && sudo chown $(id -u) ./features*'
