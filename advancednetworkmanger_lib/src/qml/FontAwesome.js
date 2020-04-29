
.pragma library

//a wrapper that allows easy coloring and adds a space at the end
function icon(symbols, color) {
  var colorStart="";
  var colorEnd="";
  if(color!=null) //implicit conversion is intentional
  {
    colorStart="<font color='"+color+"'>";
    colorEnd="</font>";
  }
  return colorStart+symbols+" "+colorEnd;
}

var fa_adjust                  = "\uf042"
var fa_adn                     = "\uf170"
var fa_align_center            = "\uf037"
var fa_align_justify           = "\uf039"
var fa_align_left              = "\uf036"
var fa_align_right             = "\uf038"
var fa_ambulance               = "\uf0f9"
var fa_anchor                  = "\uf13d"
var fa_android                 = "\uf17b"
var fa_angellist               = "\uf209"
var fa_angle_double_down       = "\uf103"
var fa_angle_double_left       = "\uf100"
var fa_angle_double_right      = "\uf101"
var fa_angle_double_up         = "\uf102"
var fa_angle_down              = "\uf107"
var fa_angle_left              = "\uf104"
var fa_angle_right             = "\uf105"
var fa_angle_up                = "\uf106"
var fa_apple                   = "\uf179"
var fa_archive                 = "\uf187"
var fa_area_chart              = "\uf1fe"
var fa_arrow_circle_down       = "\uf0ab"
var fa_arrow_circle_left       = "\uf0a8"
var fa_arrow_circle_o_down     = "\uf01a"
var fa_arrow_circle_o_left     = "\uf190"
var fa_arrow_circle_o_right    = "\uf18e"
var fa_arrow_circle_o_up       = "\uf01b"
var fa_arrow_circle_right      = "\uf0a9"
var fa_arrow_circle_up         = "\uf0aa"
var fa_arrow_down              = "\uf063"
var fa_arrow_left              = "\uf060"
var fa_arrow_right             = "\uf061"
var fa_arrow_up                = "\uf062"
var fa_arrows                  = "\uf047"
var fa_arrows_alt              = "\uf0b2"
var fa_arrows_h                = "\uf07e"
var fa_arrows_v                = "\uf07d"
var fa_asterisk                = "\uf069"
var fa_at                      = "\uf1fa"
var fa_automobile              = "\uf1b9"
var fa_backward                = "\uf04a"
var fa_ban                     = "\uf05e"
var fa_bank                    = "\uf19c"
var fa_bar_chart_o             = "\uf080"
var fa_barcode                 = "\uf02a"
var fa_bars                    = "\uf0c9"
var fa_beer                    = "\uf0fc"
var fa_behance                 = "\uf1b4"
var fa_behance_square          = "\uf1b5"
var fa_bell                    = "\uf0f3"
var fa_bell_o                  = "\uf0a2"
var fa_bell_slash              = "\uf1f6"
var fa_bell_slash_o            = "\uf1f7"
var fa_bicycle                 = "\uf206"
var fa_binoculars              = "\uf1e5"
var fa_birthday_cake           = "\uf1fd"
var fa_bitbucket               = "\uf171"
var fa_bitbucket_square        = "\uf172"
var fa_bitcoin                 = "\uf15a"
var fa_bold                    = "\uf032"
var fa_bolt                    = "\uf0e7"
var fa_bomb                    = "\uf1e2"
var fa_book                    = "\uf02d"
var fa_bookmark                = "\uf02e"
var fa_bookmark_o              = "\uf097"
var fa_briefcase               = "\uf0b1"
var fa_btc                     = "\uf15a"
var fa_bug                     = "\uf188"
var fa_building                = "\uf1ad"
var fa_building_o              = "\uf0f7"
var fa_bullhorn                = "\uf0a1"
var fa_bullseye                = "\uf140"
var fa_bus                     = "\uf207"
var fa_cab                     = "\uf1ba"
var fa_calculator              = "\uf1ec"
var fa_calendar                = "\uf073"
var fa_calendar_o              = "\uf133"
var fa_camera                  = "\uf030"
var fa_camera_retro            = "\uf083"
var fa_car                     = "\uf1b9"
var fa_caret_down              = "\uf0d7"
var fa_caret_left              = "\uf0d9"
var fa_caret_right             = "\uf0da"
var fa_caret_square_o_down     = "\uf150"
var fa_caret_square_o_left     = "\uf191"
var fa_caret_square_o_right    = "\uf152"
var fa_caret_square_o_up       = "\uf151"
var fa_caret_up                = "\uf0d8"
var fa_cc                      = "\uf20a"
var fa_cc_amex                 = "\uf1f3"
var fa_cc_discover             = "\uf1f2"
var fa_cc_mastercard           = "\uf1f1"
var fa_cc_paypal               = "\uf1f4"
var fa_cc_stripe               = "\uf1f5"
var fa_cc_visa                 = "\uf1f0"
var fa_certificate             = "\uf0a3"
var fa_chain                   = "\uf0c1"
var fa_chain_broken            = "\uf127"
var fa_check                   = "\uf00c"
var fa_check_circle            = "\uf058"
var fa_check_circle_o          = "\uf05d"
var fa_check_square            = "\uf14a"
var fa_check_square_o          = "\uf046"
var fa_chevron_circle_down     = "\uf13a"
var fa_chevron_circle_left     = "\uf137"
var fa_chevron_circle_right    = "\uf138"
var fa_chevron_circle_up       = "\uf139"
var fa_chevron_down            = "\uf078"
var fa_chevron_left            = "\uf053"
var fa_chevron_right           = "\uf054"
var fa_chevron_up              = "\uf077"
var fa_child                   = "\uf1ae"
var fa_circle                  = "\uf111"
var fa_circle_o                = "\uf10c"
var fa_circle_o_notch          = "\uf1ce"
var fa_circle_thin             = "\uf1db"
var fa_clipboard               = "\uf0ea"
var fa_clock_o                 = "\uf017"
var fa_close                   = "\uf00d"
var fa_cloud                   = "\uf0c2"
var fa_cloud_download          = "\uf0ed"
var fa_cloud_upload            = "\uf0ee"
var fa_cny                     = "\uf157"
var fa_code                    = "\uf121"
var fa_code_fork               = "\uf126"
var fa_codepen                 = "\uf1cb"
var fa_coffee                  = "\uf0f4"
var fa_cog                     = "\uf013"
var fa_cogs                    = "\uf085"
var fa_columns                 = "\uf0db"
var fa_comment                 = "\uf075"
var fa_comment_o               = "\uf0e5"
var fa_comments                = "\uf086"
var fa_comments_o              = "\uf0e6"
var fa_compass                 = "\uf14e"
var fa_compress                = "\uf066"
var fa_copy                    = "\uf0c5"
var fa_copyright               = "\uf1f9"
var fa_credit_card             = "\uf09d"
var fa_crop                    = "\uf125"
var fa_crosshairs              = "\uf05b"
var fa_css3                    = "\uf13c"
var fa_cube                    = "\uf1b2"
var fa_cubes                   = "\uf1b3"
var fa_cut                     = "\uf0c4"
var fa_cutlery                 = "\uf0f5"
var fa_dashboard               = "\uf0e4"
var fa_database                = "\uf1c0"
var fa_dedent                  = "\uf03b"
var fa_delicious               = "\uf1a5"
var fa_desktop                 = "\uf108"
var fa_deviantart              = "\uf1bd"
var fa_digg                    = "\uf1a6"
var fa_dollar                  = "\uf155"
var fa_dot_circle_o            = "\uf192"
var fa_download                = "\uf019"
var fa_dribbble                = "\uf17d"
var fa_dropbox                 = "\uf16b"
var fa_drupal                  = "\uf1a9"
var fa_edit                    = "\uf044"
var fa_eject                   = "\uf052"
var fa_ellipsis_h              = "\uf141"
var fa_ellipsis_v              = "\uf142"
var fa_empire                  = "\uf1d1"
var fa_envelope                = "\uf0e0"
var fa_envelope_o              = "\uf003"
var fa_envelope_square         = "\uf199"
var fa_eraser                  = "\uf12d"
var fa_eur                     = "\uf153"
var fa_euro                    = "\uf153"
var fa_exchange                = "\uf0ec"
var fa_exclamation             = "\uf12a"
var fa_exclamation_circle      = "\uf06a"
var fa_exclamation_triangle    = "\uf071"
var fa_expand                  = "\uf065"
var fa_external_link           = "\uf08e"
var fa_external_link_square    = "\uf14c"
var fa_eye                     = "\uf06e"
var fa_eye_slash               = "\uf070"
var fa_eyedropper              = "\uf1fb"
var fa_facebook                = "\uf09a"
var fa_facebook_square         = "\uf082"
var fa_fast_backward           = "\uf049"
var fa_fast_forward            = "\uf050"
var fa_fax                     = "\uf1ac"
var fa_female                  = "\uf182"
var fa_fighter_jet             = "\uf0fb"
var fa_file                    = "\uf15b"
var fa_file_archive_o          = "\uf1c6"
var fa_file_audio_o            = "\uf1c7"
var fa_file_code_o             = "\uf1c9"
var fa_file_excel_o            = "\uf1c3"
var fa_file_image_o            = "\uf1c5"
var fa_file_movie_o            = "\uf1c8"
var fa_file_o                  = "\uf016"
var fa_file_pdf_o              = "\uf1c1"
var fa_file_photo_o            = "\uf1c5"
var fa_file_picture_o          = "\uf1c5"
var fa_file_powerpoint_o       = "\uf1c4"
var fa_file_sound_o            = "\uf1c7"
var fa_file_text               = "\uf15c"
var fa_file_text_o             = "\uf0f6"
var fa_file_video_o            = "\uf1c8"
var fa_file_word_o             = "\uf1c2"
var fa_file_zip_o              = "\uf1c6"
var fa_files_o                 = "\uf0c5"
var fa_film                    = "\uf008"
var fa_filter                  = "\uf0b0"
var fa_fire                    = "\uf06d"
var fa_fire_extinguisher       = "\uf134"
var fa_flag                    = "\uf024"
var fa_flag_checkered          = "\uf11e"
var fa_flag_o                  = "\uf11d"
var fa_flash                   = "\uf0e7"
var fa_flask                   = "\uf0c3"
var fa_flickr                  = "\uf16e"
var fa_floppy_o                = "\uf0c7"
var fa_folder                  = "\uf07b"
var fa_folder_o                = "\uf114"
var fa_folder_open             = "\uf07c"
var fa_folder_open_o           = "\uf115"
var fa_font                    = "\uf031"
var fa_forward                 = "\uf04e"
var fa_foursquare              = "\uf180"
var fa_frown_o                 = "\uf119"
var fa_futbol_o                = "\uf1e3"
var fa_gamepad                 = "\uf11b"
var fa_gavel                   = "\uf0e3"
var fa_gbp                     = "\uf154"
var fa_ge                      = "\uf1d1"
var fa_gear                    = "\uf013"
var fa_gears                   = "\uf085"
var fa_gift                    = "\uf06b"
var fa_git                     = "\uf1d3"
var fa_git_square              = "\uf1d2"
var fa_github                  = "\uf09b"
var fa_github_alt              = "\uf113"
var fa_github_square           = "\uf092"
var fa_gittip                  = "\uf184"
var fa_glass                   = "\uf000"
var fa_globe                   = "\uf0ac"
var fa_google                  = "\uf1a0"
var fa_google_plus             = "\uf0d5"
var fa_google_plus_square      = "\uf0d4"
var fa_google_wallet           = "\uf1ee"
var fa_graduation_cap          = "\uf19d"
var fa_group                   = "\uf0c0"
var fa_h_square                = "\uf0fd"
var fa_hacker_news             = "\uf1d4"
var fa_hand_o_down             = "\uf0a7"
var fa_hand_o_left             = "\uf0a5"
var fa_hand_o_right            = "\uf0a4"
var fa_hand_o_up               = "\uf0a6"
var fa_hdd_o                   = "\uf0a0"
var fa_header                  = "\uf1dc"
var fa_headphones              = "\uf025"
var fa_heart                   = "\uf004"
var fa_heart_o                 = "\uf08a"
var fa_history                 = "\uf1da"
var fa_home                    = "\uf015"
var fa_hospital_o              = "\uf0f8"
var fa_html5                   = "\uf13b"
var fa_ils                     = "\uf20b"
var fa_image                   = "\uf03e"
var fa_inbox                   = "\uf01c"
var fa_indent                  = "\uf03c"
var fa_info                    = "\uf129"
var fa_info_circle             = "\uf05a"
var fa_inr                     = "\uf156"
var fa_instagram               = "\uf16d"
var fa_institution             = "\uf19c"
var fa_ioxhost                 = "\uf208"
var fa_italic                  = "\uf033"
var fa_joomla                  = "\uf1aa"
var fa_jpy                     = "\uf157"
var fa_jsfiddle                = "\uf1cc"
var fa_key                     = "\uf084"
var fa_keyboard_o              = "\uf11c"
var fa_krw                     = "\uf159"
var fa_language                = "\uf1ab"
var fa_laptop                  = "\uf109"
var fa_lastfm                  = "\uf202"
var fa_lastfm_square           = "\uf203"
var fa_leaf                    = "\uf06c"
var fa_legal                   = "\uf0e3"
var fa_lemon_o                 = "\uf094"
var fa_level_down              = "\uf149"
var fa_level_up                = "\uf148"
var fa_life_bouy               = "\uf1cd"
var fa_life_buoy               = "\uf1cd"
var fa_life_ring               = "\uf1cd"
var fa_life_saver              = "\uf1cd"
var fa_lightbulb_o             = "\uf0eb"
var fa_line_chart              = "\uf201"
var fa_link                    = "\uf0c1"
var fa_linkedin                = "\uf0e1"
var fa_linkedin_square         = "\uf08c"
var fa_linux                   = "\uf17c"
var fa_list                    = "\uf03a"
var fa_list_alt                = "\uf022"
var fa_list_ol                 = "\uf0cb"
var fa_list_ul                 = "\uf0ca"
var fa_location_arrow          = "\uf124"
var fa_lock                    = "\uf023"
var fa_long_arrow_down         = "\uf175"
var fa_long_arrow_left         = "\uf177"
var fa_long_arrow_right        = "\uf178"
var fa_long_arrow_up           = "\uf176"
var fa_magic                   = "\uf0d0"
var fa_magnet                  = "\uf076"
var fa_mail_forward            = "\uf064"
var fa_mail_reply              = "\uf112"
var fa_mail_reply_all          = "\uf122"
var fa_male                    = "\uf183"
var fa_map_marker              = "\uf041"
var fa_maxcdn                  = "\uf136"
var fa_meanpath                = "\uf20c"
var fa_medkit                  = "\uf0fa"
var fa_meh_o                   = "\uf11a"
var fa_microphone              = "\uf130"
var fa_microphone_slash        = "\uf131"
var fa_minus                   = "\uf068"
var fa_minus_circle            = "\uf056"
var fa_minus_square            = "\uf146"
var fa_minus_square_o          = "\uf147"
var fa_mobile                  = "\uf10b"
var fa_mobile_phone            = "\uf10b"
var fa_money                   = "\uf0d6"
var fa_moon_o                  = "\uf186"
var fa_mortar_board            = "\uf19d"
var fa_music                   = "\uf001"
var fa_navicon                 = "\uf0c9"
var fa_newspaper_o             = "\uf1ea"
var fa_openid                  = "\uf19b"
var fa_outdent                 = "\uf03b"
var fa_pagelines               = "\uf18c"
var fa_paint_brush             = "\uf1fc"
var fa_paper_plane             = "\uf1d8"
var fa_paper_plane_o           = "\uf1d9"
var fa_paperclip               = "\uf0c6"
var fa_paragraph               = "\uf1dd"
var fa_paste                   = "\uf0ea"
var fa_pause                   = "\uf04c"
var fa_paw                     = "\uf1b0"
var fa_paypal                  = "\uf1ed"
var fa_pencil                  = "\uf040"
var fa_pencil_square           = "\uf14b"
var fa_pencil_square_o         = "\uf044"
var fa_phone                   = "\uf095"
var fa_phone_square            = "\uf098"
var fa_photo                   = "\uf03e"
var fa_picture_o               = "\uf03e"
var fa_pie_chart               = "\uf200"
var fa_pied_piper              = "\uf1a7"
var fa_pied_piper_alt          = "\uf1a8"
var fa_pinterest               = "\uf0d2"
var fa_pinterest_square        = "\uf0d3"
var fa_plane                   = "\uf072"
var fa_play                    = "\uf04b"
var fa_play_circle             = "\uf144"
var fa_play_circle_o           = "\uf01d"
var fa_plug                    = "\uf1e6"
var fa_plus                    = "\uf067"
var fa_plus_circle             = "\uf055"
var fa_plus_square             = "\uf0fe"
var fa_plus_square_o           = "\uf196"
var fa_power_off               = "\uf011"
var fa_print                   = "\uf02f"
var fa_puzzle_piece            = "\uf12e"
var fa_qq                      = "\uf1d6"
var fa_qrcode                  = "\uf029"
var fa_question                = "\uf128"
var fa_question_circle         = "\uf059"
var fa_quote_left              = "\uf10d"
var fa_quote_right             = "\uf10e"
var fa_ra                      = "\uf1d0"
var fa_random                  = "\uf074"
var fa_rebel                   = "\uf1d0"
var fa_recycle                 = "\uf1b8"
var fa_reddit                  = "\uf1a1"
var fa_reddit_square           = "\uf1a2"
var fa_refresh                 = "\uf021"
var fa_remove                  = "\uf00d"
var fa_renren                  = "\uf18b"
var fa_reorder                 = "\uf0c9"
var fa_repeat                  = "\uf01e"
var fa_reply                   = "\uf112"
var fa_reply_all               = "\uf122"
var fa_retweet                 = "\uf079"
var fa_rmb                     = "\uf157"
var fa_road                    = "\uf018"
var fa_rocket                  = "\uf135"
var fa_rotate_left             = "\uf0e2"
var fa_rotate_right            = "\uf01e"
var fa_rouble                  = "\uf158"
var fa_rss                     = "\uf09e"
var fa_rss_square              = "\uf143"
var fa_rub                     = "\uf158"
var fa_ruble                   = "\uf158"
var fa_rupee                   = "\uf156"
var fa_save                    = "\uf0c7"
var fa_scissors                = "\uf0c4"
var fa_search                  = "\uf002"
var fa_search_minus            = "\uf010"
var fa_search_plus             = "\uf00e"
var fa_send                    = "\uf1d8"
var fa_send_o                  = "\uf1d9"
var fa_server                  = "\uf233"
var fa_share                   = "\uf064"
var fa_share_alt               = "\uf1e0"
var fa_share_alt_square        = "\uf1e1"
var fa_share_square            = "\uf14d"
var fa_share_square_o          = "\uf045"
var fa_shekel                  = "\uf20b"
var fa_sheqel                  = "\uf20b"
var fa_shield                  = "\uf132"
var fa_shopping_cart           = "\uf07a"
var fa_sign_in                 = "\uf090"
var fa_sign_out                = "\uf08b"
var fa_signal                  = "\uf012"
var fa_sitemap                 = "\uf0e8"
var fa_skype                   = "\uf17e"
var fa_slack                   = "\uf198"
var fa_sliders                 = "\uf1de"
var fa_slideshare              = "\uf1e7"
var fa_smile_o                 = "\uf118"
var fa_soccer_ball_o           = "\uf1e3"
var fa_sort                    = "\uf0dc"
var fa_sort_alpha_asc          = "\uf15d"
var fa_sort_alpha_desc         = "\uf15e"
var fa_sort_amount_asc         = "\uf160"
var fa_sort_amount_desc        = "\uf161"
var fa_sort_asc                = "\uf0de"
var fa_sort_desc               = "\uf0dd"
var fa_sort_down               = "\uf0dd"
var fa_sort_numeric_asc        = "\uf162"
var fa_sort_numeric_desc       = "\uf163"
var fa_sort_up                 = "\uf0de"
var fa_soundcloud              = "\uf1be"
var fa_space_shuttle           = "\uf197"
var fa_spinner                 = "\uf110"
var fa_spoon                   = "\uf1b1"
var fa_spotify                 = "\uf1bc"
var fa_square                  = "\uf0c8"
var fa_square_o                = "\uf096"
var fa_stack_exchange          = "\uf18d"
var fa_stack_overflow          = "\uf16c"
var fa_star                    = "\uf005"
var fa_star_half               = "\uf089"
var fa_star_half_empty         = "\uf123"
var fa_star_half_full          = "\uf123"
var fa_star_half_o             = "\uf123"
var fa_star_o                  = "\uf006"
var fa_steam                   = "\uf1b6"
var fa_steam_square            = "\uf1b7"
var fa_step_backward           = "\uf048"
var fa_step_forward            = "\uf051"
var fa_stethoscope             = "\uf0f1"
var fa_stop                    = "\uf04d"
var fa_strikethrough           = "\uf0cc"
var fa_stumbleupon             = "\uf1a4"
var fa_stumbleupon_circle      = "\uf1a3"
var fa_subscript               = "\uf12c"
var fa_suitcase                = "\uf0f2"
var fa_sun_o                   = "\uf185"
var fa_superscript             = "\uf12b"
var fa_support                 = "\uf1cd"
var fa_table                   = "\uf0ce"
var fa_tablet                  = "\uf10a"
var fa_tachometer              = "\uf0e4"
var fa_tag                     = "\uf02b"
var fa_tags                    = "\uf02c"
var fa_tasks                   = "\uf0ae"
var fa_taxi                    = "\uf1ba"
var fa_tencent_weibo           = "\uf1d5"
var fa_terminal                = "\uf120"
var fa_text_height             = "\uf034"
var fa_text_width              = "\uf035"
var fa_th                      = "\uf00a"
var fa_th_large                = "\uf009"
var fa_th_list                 = "\uf00b"
var fa_thumb_tack              = "\uf08d"
var fa_thumbs_down             = "\uf165"
var fa_thumbs_o_down           = "\uf088"
var fa_thumbs_o_up             = "\uf087"
var fa_thumbs_up               = "\uf164"
var fa_ticket                  = "\uf145"
var fa_times                   = "\uf00d"
var fa_times_circle            = "\uf057"
var fa_times_circle_o          = "\uf05c"
var fa_tint                    = "\uf043"
var fa_toggle_down             = "\uf150"
var fa_toggle_left             = "\uf191"
var fa_toggle_off              = "\uf204"
var fa_toggle_on               = "\uf205"
var fa_toggle_right            = "\uf152"
var fa_toggle_up               = "\uf151"
var fa_trash                   = "\uf1f8"
var fa_trash_o                 = "\uf014"
var fa_tree                    = "\uf1bb"
var fa_trello                  = "\uf181"
var fa_trophy                  = "\uf091"
var fa_truck                   = "\uf0d1"
var fa_try                     = "\uf195"
var fa_tty                     = "\uf1e4"
var fa_tumblr                  = "\uf173"
var fa_tumblr_square           = "\uf174"
var fa_turkish_lira            = "\uf195"
var fa_twitch                  = "\uf1e8"
var fa_twitter                 = "\uf099"
var fa_twitter_square          = "\uf081"
var fa_umbrella                = "\uf0e9"
var fa_underline               = "\uf0cd"
var fa_undo                    = "\uf0e2"
var fa_university              = "\uf19c"
var fa_unlink                  = "\uf127"
var fa_unlock                  = "\uf09c"
var fa_unlock_alt              = "\uf13e"
var fa_unsorted                = "\uf0dc"
var fa_upload                  = "\uf093"
var fa_usd                     = "\uf155"
var fa_user                    = "\uf007"
var fa_user_md                 = "\uf0f0"
var fa_users                   = "\uf0c0"
var fa_video_camera            = "\uf03d"
var fa_vimeo_square            = "\uf194"
var fa_vine                    = "\uf1ca"
var fa_vk                      = "\uf189"
var fa_volume_down             = "\uf027"
var fa_volume_off              = "\uf026"
var fa_volume_up               = "\uf028"
var fa_warning                 = "\uf071"
var fa_wechat                  = "\uf1d7"
var fa_weibo                   = "\uf18a"
var fa_weixin                  = "\uf1d7"
var fa_wheelchair              = "\uf193"
var fa_wifi                    = "\uf1eb"
var fa_windows                 = "\uf17a"
var fa_won                     = "\uf159"
var fa_wordpress               = "\uf19a"
var fa_wrench                  = "\uf0ad"
var fa_xing                    = "\uf168"
var fa_xing_square             = "\uf169"
var fa_yahoo                   = "\uf19e"
var fa_yelp                    = "\uf1e9"
var fa_yen                     = "\uf157"
var fa_youtube                 = "\uf167"
var fa_youtube_play            = "\uf16a"
var fa_youtube_square          = "\uf166"
