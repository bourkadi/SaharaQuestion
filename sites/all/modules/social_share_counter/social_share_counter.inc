<?php

/**
 * @file
 * File contains functions for individual share count from all Social service.
 */
/**
 * Function to get share count from facebook.
 * @param string $url
 */
function get_count_facebook($url) {
  $count = 0;
  $response = _social_share_counter_parse("http://graph.facebook.com/?id=" . $url);
  $result = json_decode($response);
  if (isset($result->shares)) {
    $count = $result->shares;
  }

  return $count;
}

/**
 * Function to get share count from Twitter.
 * @param string $url
 */
function get_count_twitter($url) {
  $count = 0;
  $response = _social_share_counter_parse("http://urls.api.twitter.com/1/urls/count.json?url=" . $url );
  $result = json_decode($response);
  if (isset($result->count)) {
    $count = $result->count;
  }
  return $count;
}

/**
 * Function to get share count from LinkedIn.
 * @param string $url
 */
function get_count_linkedin($url) {
  $count = 0;
  $response = _social_share_counter_parse("http://www.linkedin.com/countserv/count/share?url=" . $url );
  $response_body_clean = preg_replace( "/(^IN\.Tags\.Share\.handleCount\(|\);$)/", "", $response);
  $result = json_decode($response_body_clean);
  if (isset($result->count)) {
    $count = $result->count;
  }
  return $count;
}

/**
 * Function to get share count from GooglePlus.
 * @param string $url
 */
function get_count_googleplus($url) {
  $count = 0;
  $response = _social_share_counter_parse("https://plusone.google.com/u/0/_/+1/fastbutton?url=" . $url . "&count=true");

  $dom = new DOMDocument();
  $dom->preserveWhiteSpace = FALSE;
  @$dom->loadHTML($response);
  $domxpath = new DOMXPath($dom);

  $filtered = $domxpath->query("//div[@id='aggregateCount']");
  if (isset($filtered->item(0)->nodeValue)) {
    $count = str_replace('>', '', $filtered->item(0)->nodeValue);
  }
  return $count;
}

/**
 * Function to get share count from StumbleUpon.
 * @param string $url
 */
function get_count_stumbleupon($url) {
  $count = 0;
  $response = _social_share_counter_parse("http://www.stumbleupon.com/services/1.01/badge.getinfo?url=" . $url);

  $result = json_decode($response);
  if (isset($result->result->views)) {
    $count = $result->result->views;
  }
  return $count;
}

/**
 * Funtion to get share count from Pinterest.
 * @param string $url
 */
function get_count_pinterest($url) {
  $count = 0;
  $response = _social_share_counter_parse("http://api.pinterest.com/v1/urls/count.json?callback=count&url=" . $url);
  $response = preg_replace('/^.*count\(/', '', $response);
  $response = preg_replace('/\)$/', '', $response);
  $result = json_decode( $response );

  if (isset($result->count)) {
    $count = (int) $result->count;
  }
  return $count;
}
