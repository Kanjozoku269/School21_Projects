#!/bin/bash

if [[ $CI_JOB_STATUS == 'success' ]]; then
    CI_JOB_STATUS="Success ✅"
elif [[ $CI_JOB_STATUS == 'failed' ]]; then
    CI_JOB_STATUS="Failed ❌"
else
	CI_JOB_STATUS="Canceled 🤔"
fi    

TELEGRAM_USER_ID=338395893
TELEGRAM_BOT_TOKEN=6263647712:AAFw4z9DzG4nIdzxMSoU2kA5dp2w7a8rCVg

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Status:

Job name: $CI_JOB_NAME%0A%0A
Project:+$CI_PROJECT_NAME%0A
Branch:+$CI_COMMIT_REF_SLUG%0A%0A
Status:+$CI_JOB_STATUS"
curl -s -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
