<?php

/**
 * @file
 * Administrative page callbacks for the webspeech module.
 */

/**
 * Configuration form for WebSpeech.
 */
function webspeech_config($form, &$form_state) {
  $form['demo'] = array(
    '#markup' => l(t('Demo page'), 'webspeech/demo'),
  );

  $form['server'] = array(
    '#type' => 'textfield',
    '#title' => t('WebSpeech server URL'),
    '#default_value' => variable_get('webspeech_server_url',
        'http://wa.eguidedog.net/cgi-bin/ekho.pl'),
  );


  $form['variant'] = array(
    '#type' => 'select',
    '#title' => t('Default genre setting type'),
    '#options' => array(
      '' => t('Normal'),
      'm1' => t('Male 1'),
      'm2' => t('Male 2'),
      'm3' => t('Male 3'),
      'm4' => t('Male 4'),
      'm5' => t('Male 5'),
      'f1' => t('Female 1'),
      'f2' => t('Female 2'),
      'f3' => t('Female 3'),
      'f4' => t('Female 4'),
      'f5' => t('Female 5'),
      'klatt' => t('klatt'),
      'klatt2' => t('klatt2'),
      'klatt3' => t('klatt3'),
    ),
    '#default_value' => variable_get('webspeech_variant', 'm1'),
  );

  $form['pitch'] = array(
    '#type' => 'textfield',
    '#title' => t('Pitch'),
    '#description' => t('Adjusts the pitch in a range of 0 to 99. The default is 50.'),
    '#default_value' => variable_get('webspeech_pitch', 50),
  );

  $form['volume'] = array(
    '#type' => 'textfield',
    '#title' => t('Volume'),
    '#description' => t('Sets amplitude (volume) in a range of 0 to 200. The default is 100.'),
    '#default_value' => variable_get('webspeech_volume', 100),
  );

  $form['speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Speed'),
    '#description' => t('Sets the speed in words-per-minute (approximate values for the default English voice, others may differ slightly). The default value is 175. The lower limit is 80. There is no upper limit, but about 500 is probably a practical maximum.'),
    '#default_value' => variable_get('webspeech_speed', 175),
  );

  $form['voice-setting-type'] = array(
    '#type' => 'radios',
    '#title' => t('Default voice setting type'),
    '#options' => array('text' => t('text'), 'select' => t('select')),
    '#default_value' => variable_get('webspeech_voice_setting_type', 'select'),
  );

  $form['voice'] = array(
    '#type' => 'textfield',
    '#title' => t('Default voice'),
    '#description' => t('Voice value should be supported by WebSpeech server. Default server supports "EkhoMandarin", "EkhoCantonese", "EkhoTibetan", "EkhoKorean" and any voice value supported by eSpeak like "en", "fr", "de+f2" etc.'),
    '#default_value' => variable_get('webspeech_default_voice', 'en'),
    '#states' => array(
      'visible' => array(
        ':input[name="voice-setting-type"]' => array('value' => 'text'),
      )),
  );

  $form['voice-select'] = array(
    '#type' => 'select',
    '#title' => t('Default voice'),
    '#description' => t('This is an incomplete selections of default WebSpeech server. It may not supported by other server. Please supplied the voice parameter in text rather than selection if this list does not apply your case.'),
    '#states' => array(
      'visible' => array(
        ':input[name="voice-setting-type"]' => array('value' => 'select'),
      )),
    '#default_value' => variable_get('webspeech_default_voice', 'en'),
    '#options' => array(
      'EkhoMandarin' => t('Mandarin (Standard Chinese, Yali)'),
      'EkhoCantonese' => t('Cantonese (Wong)'),
      'EkhoEnglish' => t('English (kal_diphone)'),
      'EkhoHakka' => t('Hakka'),
      'EkhoNgangien' => t('Ngangien (Ancient Chinese)'),
      'EkhoTibetan' => t('Tibetan'),
      'EkhoKorean' => t('Korean'),
      'af' => t('Afrikaans'),
      'bs' => t('Bosnian'),
      'ca' => t('Catalan'),
      'cs' => t('Czech'),
      'cy' => t('Welsh'),
      'da' => t('Danish'),
      'de' => t('German'),
      'el' => t('Greek'),
      'en' => t('English'),
      'en-sc' => t('English (Scottish)'),
      'en-uk' => t('English (UK)'),
      'en-uk-north' => t('English (Lancashire)'),
      'en-uk-rp' => t('English (uk-rp)'),
      'en-uk-wmids' => t('English (wmids)'),
      'en-us' => t('English (US)'),
      'en-wi' => t('English (West Indies)'),
      'eo' => t('Esperanto'),
      'es' => t('Spanish'),
      'es-la' => t('Spanish (Latin American)'),
      'fi' => t('Finnish'),
      'fr' => t('French'),
      'fr-be' => t('French (Belgium)'),
      'grc' => t('Greek (ancient)'),
      'hi' => t('Hindi'),
      'hr' => t('Croatian'),
      'hu' => t('Hungarian'),
      'hy' => t('Armenian'),
      'hy-west' => t('Armenian (west)'),
      'id' => t('Indonesian'),
      'is' => t('Icelandic'),
      'it' => t('Italian'),
      'jbo' => t('Lojjban'),
      'ku' => t('Kurdish'),
      'la' => t('Latin'),
      'lv' => t('Latvian'),
      'mk' => t('Macedonian'),
      'nci' => t('Nahuatl (classical)'),
      'nl' => t('Dutch'),
      'no' => t('Norwegian'),
      'pap' => t('Papiamento'),
      'pl' => t('Polish'),
      'pt' => t('Brazil'),
      'pt-pt' => t('Portugal'),
      'ro' => t('Romanian'),
      'ru' => t('Russian'),
      'sk' => t('Slovak'),
      'sq' => t('Albanian'),
      'sr' => t('Serbian'),
      'sv' => t('Swedish'),
      'sw' => t('Swahihi'),
      'ta' => t('Tamil'),
      'tr' => t('Turkish'),
      'vi' => t('Vietnam'),
      'zh' => t('Mandarin (eSpeak)'),
      'zh-yue' => t('Cantonese (eSpeak)'),
    ),
  );

  if (!webspeech_initialize()) {
    drupal_set_error(t('Fail to initialize WebSpeech.', 'error'));
  }

  $form['test-text'] = array(
    '#type' => 'textfield',
    '#title' => t('Text for testing'),
    '#prefix' => '<div class="container-inline">',
  );

  $form['test-button'] = array(
    '#type' => 'button',
    '#value' => t('test'),
    '#suffix' => '</div>',
    '#attributes' => array('onclick' => 'testWebSpeech(); return false;'),
  );

  drupal_add_js('
    function testWebSpeech() {
      var voice = "";
      if (jQuery("#edit-voice-setting-type-text").attr("checked")) {
        voice = jQuery("#edit-voice").val();
      }
      else {
        voice = jQuery("#edit-voice-select option:selected").val();
      }

      variant = jQuery("#edit-variant-setting-type option:selected").val();
      if (variant != "") {
        voice += "-" + variant;
      }

      speedDelta = jQuery("#edit-speed").val();
      pitchDelta = jQuery("#edit-pitch").val();
      volumeDelta = jQuery("#edit-volume").val();

      WebSpeech.setVoice(voice);
      WebSpeech.setSpeedDelta(speedDelta);
      WebSpeech.setPitchDelta(pitchDelta);
      WebSpeech.setVolumeDelta(volumeDelta);
      WebSpeech.speak(jQuery("#edit-test-text").val());
    }', 'inline');

  $form['content-id'] = array(
    '#type' => 'textfield',
    '#title' => t('Element ID'),
    '#description' => t('It\'s the id attribute of an HTML element. Content in the DOM tree of this element will be read after "Read Content" button is clicked.'),
    '#default_value' => variable_get('webspeech_content_id', 'content'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}


function webspeech_config_validate($form, &$form_state) {
	if(!is_numeric($form_state['values']['pitch']))
		form_set_error('pitch', t('The "Pitch" value must be a number! What are you doing???'));
	if($form_state['values']['pitch'] < 0)
		form_set_error('pitch', t('The "Pitch" value must be greater than or equal to zero.'));
	if($form_state['values']['pitch'] > 99)
		form_set_error('pitch', t('The "Pitch" value must be less than or equal to 99.'));

	if(!is_numeric($form_state['values']['volume']))
		form_set_error('volume', t('The "Volume" value must be a number! What are you doing???'));
	if($form_state['values']['volume'] < 0)
		form_set_error('volume', t('The "Volume" value must be greater than or equal to zero.'));
	if($form_state['values']['volume'] > 200)
		form_set_error('volume', t('The "Volume" value must be less than or equal to 200.'));

	if(!is_numeric($form_state['values']['speed']))
		form_set_error('speed', t('The "Speed" value must be a number! What are you doing???'));
	if($form_state['values']['speed'] < 80)
		form_set_error('speed', t('The "Speed" value must be greater than or equal to 80.'));
	if($form_state['values']['speed'] > 500)
		form_set_error('speed', t('The "Speed" value must be less than or equal to 500.'));

}

/**
 * Submit handler of configuration form.
 */
function webspeech_config_submit($form, &$form_state) {
  variable_set('webspeech_server_url', $form_state['values']['server']);
  variable_set('webspeech_content_id', $form_state['values']['content-id']);
  variable_set('webspeech_voice_setting_type', $form_state['values']['voice-setting-type']);

  variable_set('webspeech_variant', $form_state['values']['variant']);
  variable_set('webspeech_pitch', $form_state['values']['pitch']);
  variable_set('webspeech_volume', $form_state['values']['volume']);
  variable_set('webspeech_speed', $form_state['values']['speed']);

  if ($form_state['values']['voice-setting-type'] == 'select') {
    variable_set('webspeech_default_voice', $form_state['values']['voice-select']);
  }
  else {
    // 'text' type.
    variable_set('webspeech_default_voice', $form_state['values']['voice']);
  }

  drupal_set_message(t('The configuration has been successfully changed.'));
}
