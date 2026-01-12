export class ApiClient {
  static async get(url: string) {
    try {
      const controller = new AbortController();
      const timeoutId = setTimeout(() => controller.abort(), 5000);
      const res = await fetch(url, { signal: controller.signal });
      clearTimeout(timeoutId);
      if (!res.ok) throw new Error(`HTTP error! status: ${res.status}`);
      return await res.json();
    } catch (e) {
      console.error(`GET ${url} failed`, e);
      throw e;
    }
  }

  static async post(url: string, data: any) {
    try {
      const controller = new AbortController();
      const timeoutId = setTimeout(() => controller.abort(), 5000);
      const res = await fetch(url, {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: new URLSearchParams(data),
        signal: controller.signal
      });
      clearTimeout(timeoutId);
      if (!res.ok) throw new Error(`HTTP error! status: ${res.status}`);
      return await res.json();
    } catch (e) {
      console.error(`POST ${url} failed`, e);
      throw e;
    }
  }

  static async getConfig() {
    return this.get('/config');
  }

  static async getStats() {
    return this.get(`/stats?t=${Date.now()}`);
  }

  static async syncStats(stats: { count: number; duration: number }) {
    return this.post('/sync_stats', { plain: JSON.stringify(stats) });
  }

  static async resetStats() {
    return this.post('/reset_stats', {});
  }

  static async debug(pin: number, angle: number) {
    return this.post('/debug', { pin, angle });
  }
}
