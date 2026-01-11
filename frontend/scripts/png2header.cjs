const fs = require('fs');
const path = require('path');

const iconPath = process.argv[2];
const outPath = process.argv[3];

if (!iconPath || !outPath) {
    console.error("Usage: node png2header.js <input_png> <output_h>");
    process.exit(1);
}

const buffer = fs.readFileSync(iconPath);
const hex = [];
for (const byte of buffer) {
    hex.push('0x' + byte.toString(16).padStart(2, '0'));
}

const content = `#ifndef ICON_DATA_H
#define ICON_DATA_H

const unsigned char icon_png[] = {
${hex.join(', ')}
};
const unsigned int icon_png_len = ${buffer.length};

#endif
`;

fs.writeFileSync(outPath, content);
console.log(`Converted ${iconPath} to ${outPath} (${buffer.length} bytes)`);
