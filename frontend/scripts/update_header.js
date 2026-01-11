
import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const htmlPath = path.join(__dirname, '../dist/index.html');
const headerPath = path.join(__dirname, '../../src/html_content.h');

try {
    const htmlContent = fs.readFileSync(htmlPath, 'utf8');

    // C++11 raw string literal format: R"rawliteral(...)rawliteral"
    const headerContent = `const char* htmlPage = R"rawliteral(${htmlContent})rawliteral";\n`;

    fs.writeFileSync(headerPath, headerContent);
    console.log(`✅ Updated ${headerPath} with new HTML content (${htmlContent.length} bytes)`);

} catch (error) {
    console.error('❌ Error updating header file:', error);
    process.exit(1);
}
