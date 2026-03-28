import { defineConfig } from "vitepress";

const STANDARDS = [
  { id: "cpp98", label: "C++98", dir: "C++98", accent: "#F59E0B", core: 52, stl: 161, year: 1998, codename: "The Foundation" },
  { id: "cpp03", label: "C++03", dir: "C++03", accent: "#94A3B8", core: 3,  stl: 2,   year: 2003, codename: "The Refinement" },
  { id: "cpp11", label: "C++11", dir: "C++11", accent: "#06B6D4", core: 53, stl: 160, year: 2011, codename: "The Modern Era" },
  { id: "cpp14", label: "C++14", dir: "C++14", accent: "#10B981", core: 10, stl: 13,  year: 2014, codename: "The Polish" },
  { id: "cpp17", label: "C++17", dir: "C++17", accent: "#3B82F6", core: 19, stl: 78,  year: 2017, codename: "The Pragmatic" },
  { id: "cpp20", label: "C++20", dir: "C++20", accent: "#8B5CF6", core: 39, stl: 245, year: 2020, codename: "The Big Four" },
  { id: "cpp23", label: "C++23", dir: "C++23", accent: "#EC4899", core: 13, stl: 76,  year: 2023, codename: "The Refinement II" },
  { id: "cpp26", label: "C++26", dir: "C++26", accent: "#F43F5E", core: 11, stl: 33,  year: 2026, codename: "The Future" },
];

const sidebar = STANDARDS.map((s) => ({
  text: `${s.label} · ${s.core + s.stl} concepts`,
  collapsed: true,
  items: [
    { text: `Overview`, link: `/${s.id}/` },
    { text: `Core Language (${s.core})`, link: `/${s.id}/core` },
    { text: `STL & Library (${s.stl})`, link: `/${s.id}/stl` },
  ],
}));

export default defineConfig({
  title: "CodeNebula",
  description: "966+ C++ concepts across 8 standards — C++98 through C++26, with real-world scenarios and runnable examples.",
  base: "/CodeNebula/",
  srcDir: ".",
  outDir: ".vitepress/dist",
  ignoreDeadLinks: true,

  head: [
    ["link", { rel: "icon", href: "/CodeNebula/favicon.ico" }],
    ["meta", { name: "theme-color", content: "#00599C" }],
    ["meta", { property: "og:title", content: "CodeNebula — C++ Reference" }],
    ["meta", { property: "og:description", content: "966+ C++ concepts across 8 standards with real-world scenarios and examples." }],
  ],

  themeConfig: {
    logo: { light: "/logo-light.svg", dark: "/logo-dark.svg", alt: "CodeNebula" },
    siteTitle: "CodeNebula",

    nav: [
      { text: "Home", link: "/" },
      { text: "All Concepts", link: "/concepts" },
      {
        text: "Standards",
        items: STANDARDS.map((s) => ({
          text: `${s.label} — ${s.codename}`,
          link: `/${s.id}/`,
        })),
      },
      {
        text: "GitHub",
        link: "https://github.com/pruthvipanchal/CodeNebula",
        target: "_blank",
      },
    ],

    sidebar,

    outline: { level: [2, 3], label: "On this page" },

    search: { provider: "local" },

    socialLinks: [
      { icon: "github", link: "https://github.com/pruthvipanchal/CodeNebula" },
    ],

    footer: {
      message: "Released under the MIT License.",
      copyright: "Copyright © 2024-present Pruthvi Panchal · CodeNebula",
    },

    editLink: {
      pattern: "https://github.com/pruthvipanchal/CodeNebula/edit/main/docs/:path",
      text: "Edit this page on GitHub",
    },

    lastUpdated: { text: "Updated at", formatOptions: { dateStyle: "short" } },
  },

  markdown: {
    theme: { light: "github-light", dark: "github-dark" },
    languages: ["cpp", "bash", "json"],
    // Rewrite relative .cpp example file links to GitHub blob URLs
    // AND escape C++ template angle-brackets in text (e.g. std::vector<bool>)
    // so that Vue's template compiler doesn't treat them as HTML tags.
    config(md) {
      // Escape C++ template angle-brackets that markdown-it parses as html_inline
      // (e.g. std::vector<bool> → std::vector&lt;bool&gt;) so Vue doesn't
      // treat them as unclosed component tags.
      md.core.ruler.push("escape-cpp-templates", (state) => {
        for (const token of state.tokens) {
          if (token.type === "inline" && token.children) {
            for (const child of token.children) {
              if (child.type === "text") {
                child.content = child.content.replace(
                  /<([A-Za-z_][A-Za-z0-9_,\s*&:<>]*?)>/g,
                  "&lt;$1&gt;"
                );
              } else if (child.type === "html_inline") {
                // Convert C++ template tags like <bool>, <int, string> → entities
                if (/^<\/?[A-Za-z_][A-Za-z0-9_,\s*&:<>]*\/?>$/.test(child.content)) {
                  child.type = "text";
                  child.content = child.content
                    .replace(/</g, "&lt;")
                    .replace(/>/g, "&gt;");
                }
              }
            }
          }
        }
      });

      md.core.ruler.push("rewrite-cpp-links", (state) => {
        for (const token of state.tokens) {
          if (token.type === "inline" && token.children) {
            for (const child of token.children) {
              if (child.type === "link_open") {
                const hrefAttr = child.attrs?.find(([k]) => k === "href");
                if (hrefAttr && typeof hrefAttr[1] === "string") {
                  const href = hrefAttr[1] as string;
                  // Match relative links to .cpp files like ../../examples/C++11/file.cpp
                  const m = href.match(/\.\.\/\.\.\/examples\/(C\+\+\d+)\/(.+\.cpp)/);
                  if (m) {
                    hrefAttr[1] = `https://github.com/pruthvipanchal/CodeNebula/blob/main/examples/${m[1]}/${m[2]}`;
                    // Find and update the target attribute or add one
                    const targetAttr = child.attrs?.find(([k]) => k === "target");
                    if (targetAttr) {
                      targetAttr[1] = "_blank";
                    } else {
                      child.attrs = child.attrs || [];
                      child.attrs.push(["target", "_blank"]);
                      child.attrs.push(["rel", "noopener noreferrer"]);
                    }
                  }
                }
              }
            }
          }
        }
      });
    },
  },
});
